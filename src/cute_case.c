#include "cute_test.h"

#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free, NULL */



struct testcase {
	CUTE_Proc *initiate, *terminate;
	CUTE_Proc *before, *after;
	unsigned int capacity, size;
	CUTE_Test tests[];
};


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

void CUTE_runTestCase(CUTE_TestCase *const tc) {
	tc->initiate();
	for(unsigned int i = 0; i < tc->size; ++i) {
		tc->before();
		CUTE_runTest(tc->tests[i]);
		tc->after();
	}
	tc->terminate();
}
