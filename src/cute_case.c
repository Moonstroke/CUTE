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

static volatile sig_atomic_t _status;

static void _handler(const int signum) {
	static const CUTE_TestStatus statutes[32] = {
		[SIGABRT] = CUTE_RESULT_FAILURE,
		[SIGFPE] = CUTE_RESULT_ERROR,
		[SIGINT] = CUTE_RESULT_CANCELED,
		[SIGQUIT] = CUTE_RESULT_CANCELED,
		[SIGTSTP] = CUTE_RESULT_SKIPPED
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

unsigned int CUTE_getCaseTestsNumber(CUTE_TestCase *const c) {
	return c->size;
}

CUTE_TestCaseOutcome *CUTE_runTestCase(const CUTE_TestCase *const tc) {
	CUTE_TestCaseOutcome *r = CUTE_prepareOutcome(tc->size);
	tc->initiate();
	_set_handlers();
	for(unsigned int i = 0; i < tc->size; ++i) {
		_status = CUTE_RESULT_SUCCESS;
		tc->before();
		CUTE_runTest(tc->tests[i]);
		tc->after();
		r->results[i].name = CUTE_getTestName(tc->tests[i]);
		switch(r->results[i].result = _status) {
			case CUTE_RESULT_SUCCESS:
				++r->successes;
				debug("%s: success", CUTE_getTestName(tc->tests[i]));
				break;
			case CUTE_RESULT_FAILURE:
				debug("Test %s failed", CUTE_getTestName(tc->tests[i]));
				break;
			case CUTE_RESULT_ERROR:
				debug("%s test error", CUTE_getTestName(tc->tests[i]));
				break;
			case CUTE_RESULT_IGNORED:
				break; /* can't occur, only here for the warning */
			case CUTE_RESULT_SKIPPED:
				debug("test %s skipped", CUTE_getTestName(tc->tests[i]));
				continue;
			case CUTE_RESULT_CANCELED:
				debug("User interrupted %s", CUTE_getTestName(tc->tests[i]));
				for(; i < tc->size; ++i) { /* cancel all remaining tests */
					r->results[i].name = CUTE_getTestName(tc->tests[i]);
					r->results[i].result = CUTE_RESULT_CANCELED;
				}
				goto end;
		}
	}
end:
	tc->terminate();
	return r;
}
