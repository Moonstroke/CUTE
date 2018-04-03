#include "cute_test.h"

#include <clog.h> /* for debug */
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
	STATUS_FAILURE = 1, /* assertion in the test failed. = 1 to be non-zero */
	STATUS_ERROR, /* error outside of assertion (segfault, zero-division) */
	STATUS_INTERRUPT /* User cancelled */
};

static sig_atomic_t _status;

static void _handler(const int signum) {
	static const enum status statutes[32] = {
		[SIGABRT] = STATUS_FAILURE,
		[SIGFPE] = STATUS_ERROR,
		[SIGSEGV] = STATUS_ERROR,
		[SIGINT] = STATUS_INTERRUPT,
		[SIGQUIT] = STATUS_INTERRUPT,
		[SIGTSTP] = STATUS_INTERRUPT
	};
	_status = statutes[signum];
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
		CUTE_runTest(tc->tests[i]);
		switch(_status) {
			case STATUS_FAILURE:
				debug("Test failed");
				break;
			case STATUS_INTERRUPT:
				debug("User interruption");
				break;
			case STATUS_ERROR:
				debug("Test error");
				break;
		}
		tc->after();
	}
	tc->terminate();
}
