#include "cute_test.h"

#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free */

#include "cute_assert.h" /* for CUTE_assumeValue */



struct testsuite {
	unsigned int number;
	char _padding[4];
	CUTE_TestCase *cases[];
};

CUTE_TestSuite *CUTE_buildTestSuite(const unsigned int n, ...) {
	CUTE_TestSuite *const ts = malloc(sizeof(CUTE_TestSuite)
	                                  + n * sizeof(CUTE_TestCase*));
	if(ts) {
		va_list args;
		va_start(args, n);
		for(unsigned int i = 0; i < (ts->number = n); ++i) {
			ts->cases[i] = va_arg(args, CUTE_TestCase*);
		}
		va_end(args);
	}
	return ts;
}

void CUTE_destroyTestSuite(CUTE_TestSuite *const ts) {
	for(unsigned int i = 0; i < ts->number; ++i) {
		CUTE_freeTestCase(ts->cases[i]);
	}
	free(ts);
}

CUTE_RunResults **CUTE_runTestSuite(const CUTE_TestSuite *const ts) {
	CUTE_RunResults **results = malloc(ts->number * sizeof(CUTE_RunResults*));
	CUTE_assumeValue(results != NULL, NULL);
	for(unsigned int i = 0; i < ts->number; ++i) {
		results[i] = CUTE_runTestCase(ts->cases[i]);
	}
	return results;
}
