#include "cute_test.h"

#include <PUCA/funcattrs.h> /* for INLINE */
#include <signal.h> /* for sig_atomic_t, sigaction, struct sigaction, SIG* */
#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free, NULL */
#include <time.h> /* for clock_t, clock, CLOCKS_PER_SEC */

#include "cute_assert.h" /* for CUTE_assumeValue */



static volatile sig_atomic_t _status;

static void _handler(const int signum) {
	static const CUTE_TestStatus statutes[32] = {
		[SIGABRT] = CUTE_STATUS_FAILURE,
		[SIGFPE] = CUTE_STATUS_ERROR,
		[SIGINT] = CUTE_STATUS_CANCELED,
		[SIGQUIT] = CUTE_STATUS_CANCELED,
		[SIGTSTP] = CUTE_STATUS_SKIPPED
	};
	_status = statutes[signum];
}

#define SET_HANDLER_FOR(signum, sigact) \
	if(sigaction(signum, &sigact, NULL) < 0) return;

static void _set_handlers(void) {
	struct sigaction act;
	act.sa_handler = _handler; /* function to handle signals */
	act.sa_flags = 0; /* handler flags (none set) */
	sigemptyset(&act.sa_mask); /* do not block any signal */
	SET_HANDLER_FOR(SIGABRT, act); /* abort() called */
	SET_HANDLER_FOR(SIGINT, act); /* Ctrl-C typed */
	SET_HANDLER_FOR(SIGQUIT, act); /* keyboard quit, Ctrl-\ (core dump) */
	SET_HANDLER_FOR(SIGFPE, act); /* floating-point or math error */
	SET_HANDLER_FOR(SIGTSTP, act); /* terminal stop */
}

static void _noop(void) {}

static INLINE bool _ignore(const CUTE_Test t) {
	return CUTE_getTestName(t)[0] == 'I';
}

static INLINE const char *_stripignore(const CUTE_Test t) {
	return CUTE_getTestName(t) + 1;
}

CUTE_TestCase *CUTE_newTestCase(const char *const t, const unsigned int n) {
	CUTE_TestCase *const tc = malloc(sizeof(CUTE_TestCase)
	                                 + n * sizeof(CUTE_Test));
	CUTE_assumeValue(tc != NULL, NULL);
	tc->title = t;
	tc->initiate = tc->terminate = tc->before = tc->after = _noop;
	tc->number = 0;
	for(unsigned int i = 0; i < (tc->capacity = n); ++i) {
		tc->tests[i] = (CUTE_Test){NULL, ""};
	}
	return tc;
}

void CUTE_freeTestCase(CUTE_TestCase *const tc) {
	free(tc);
}

extern void CUTE_setCaseInitiate(CUTE_TestCase*, CUTE_Proc*);
extern void CUTE_setCaseTerminate(CUTE_TestCase*, CUTE_Proc*);
extern void CUTE_setCaseBefore(CUTE_TestCase*, CUTE_Proc*);
extern void CUTE_setCaseAfter(CUTE_TestCase *const tc, CUTE_Proc *const f);

bool CUTE_addCaseTest(CUTE_TestCase *const tc, CUTE_Test t) {
	if(tc->number < tc->capacity) {
		tc->tests[tc->number++] = t;
		return true;
	}
	return false;
}

extern unsigned int CUTE_getCaseTestsNumber(const CUTE_TestCase*);
extern const char *CUTE_getCaseTitle(const CUTE_TestCase*);

CUTE_RunResults *CUTE_runTestCase(const CUTE_TestCase *const tc) {
	static clock_t start, end;
	CUTE_RunResults *const r = CUTE_prepareResults(tc->title, tc->number);
	_set_handlers();
	tc->initiate();
	for(unsigned int i = 0; i < tc->number; ++i) {
		if(_ignore(tc->tests[i])) {
			r->results[i].name = _stripignore(tc->tests[i]);
			r->results[i].status = CUTE_STATUS_IGNORED;
			r->results[i].time = -1;
			continue;
		}
		_status = CUTE_STATUS_SUCCESS;
		tc->before();
		start = clock();
		CUTE_runTest(tc->tests[i]);
		end = clock();
		tc->after();
		r->results[i].name = CUTE_getTestName(tc->tests[i]);
		r->results[i].time = (end - start) / CLOCKS_PER_SEC;
		switch(r->results[i].status = _status) {
			case CUTE_STATUS_SUCCESS:
				++r->successes;
				break;
			case CUTE_STATUS_FAILURE: break;
			case CUTE_STATUS_ERROR: break;
			case CUTE_STATUS_IGNORED: break; /* can't occur, only here for the
			                                    warning */
			case CUTE_STATUS_SKIPPED:
				continue;
			case CUTE_STATUS_CANCELED:
				for(; i < tc->number; ++i) { /* cancel all remaining tests */
					r->results[i].name = CUTE_getTestName(tc->tests[i]);
					r->results[i].status = CUTE_STATUS_CANCELED;
				}
				goto end;
		}
	}
end:
	tc->terminate();
	return r;
}


#include <PUCA/end.h>
