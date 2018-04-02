#include "cute_test.h"

#include <clog.h> /* for debug */
#include <setjmp.h> /* for jmp_buf, setjmp, longjmp */
#include <signal.h> /* for sigaction, struct sigaction, SIG* */
#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free, NULL */



struct testcase {
	CUTE_Proc *initiate, *terminate;
	CUTE_Proc *before, *after;
	unsigned int capacity, size;
	CUTE_Test tests[];
};

enum status {
	STATUS_FAILURE = 1, /* to be non-zero */
	STATUS_INTERRUPT,
	STATUS_QUIT,
	STATUS_CALCERROR,
	STATUS_SEGFAULT,
	STATUS_STOPPED
};

static jmp_buf _env;

static void _handler(const int signum) {
	int status;
	switch(signum) {
		case SIGABRT: /* failure */
			debug("abort");
			status = STATUS_FAILURE;
			break;
		case SIGINT: /* keyboard Ctrl-C */
			debug("interrupt");
			status = STATUS_INTERRUPT;
			break;
		case SIGQUIT: /* keyboard quit, Ctrl-\ */
			debug("quit");
			status = STATUS_QUIT;
			break;
		case SIGFPE:
			debug("math error");
			status = STATUS_CALCERROR;
			break;
		case SIGSEGV:
			debug("segmentation fault");
			status = STATUS_SEGFAULT;
			break;
		case SIGTSTP:
			debug("terminal stop");
			status = STATUS_STOPPED;
			break;
		default:
			return;
	}
	longjmp(_env, status);
}

#define SET_HANDLER_FOR(signum, sigact) if(!sigaction(signum, &sigact, NULL));\
	else { error("Can't handle " #signum); return; }

static void _set_handlers(void) {
	struct sigaction act;
	act.sa_handler = _handler; /* function to handle signals */
	act.sa_flags = 0; /* handler flags (none set) */
	sigemptyset(&act.sa_mask); /* do not block any signal */
	SET_HANDLER_FOR(SIGABRT, act); /* abort() called */
	SET_HANDLER_FOR(SIGINT, act); /* Ctrl-C typed */
	SET_HANDLER_FOR(SIGQUIT, act); /* keyboard quit, Ctrl-\ (core dump) */
	SET_HANDLER_FOR(SIGFPE, act); /* floating-point error, or any math error */
	SET_HANDLER_FOR(SIGSEGV, act); /* segmentation fault */
	SET_HANDLER_FOR(SIGTSTP, act); /* terminal stop */
}

static void _noop(void) {}

CUTE_TestCase *CUTE_newTestCase(const unsigned int n) {
	CUTE_TestCase *const tc = malloc(sizeof(CUTE_TestCase)
	                                 + n * sizeof(CUTE_Test));
	if(tc) {
		tc->initiate = tc->terminate = tc->before = tc->after = _noop;
		tc->size = 0;
		for(unsigned int i = 0; i < (tc->capacity = n); ++i) {
			tc->tests[i] = (CUTE_Test){NULL, ""};
		}
	}
	return tc;
}

void CUTE_freeTestCase(CUTE_TestCase *const tc) {
	free(tc);
}

void CUTE_setCaseInitiate(CUTE_TestCase *const tc, CUTE_Proc *const f) {
	tc->initiate = f;
}
void CUTE_setCaseTerminate(CUTE_TestCase *const tc, CUTE_Proc *const f) {
	tc->terminate = f;
}

void CUTE_setCaseBefore(CUTE_TestCase *const tc, CUTE_Proc *const f) {
	tc->before = f;
}
void CUTE_setCaseAfter(CUTE_TestCase *const tc, CUTE_Proc *const f) {
	tc->after = f;
}

bool CUTE_addCaseTest(CUTE_TestCase *const tc, CUTE_Test t) {
	if(tc->size < tc->capacity) {
		tc->tests[tc->size++] = t;
		return true;
	}
	return false;
}

void CUTE_runTestCase(const CUTE_TestCase *const tc) {
	tc->initiate();
	_set_handlers();
	for(unsigned int i = 0; i < tc->size; ++i) {
		tc->before();
		switch(setjmp(_env)) {
			case 0: /* first return */
				CUTE_runTest(tc->tests[i]);
			default: /* jumped from the signal handler */
				/* TODO use return value of setjmp */
				break;
		}
		tc->after();
	}
	tc->terminate();
}
