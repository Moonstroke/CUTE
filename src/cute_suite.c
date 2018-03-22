#include "cute_test.h"

#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free */



struct testsuite {
	unsigned int size;
	char _padding[4];
	CUTE_TestCase *cases[];
};

CUTE_TestSuite *CUTE_buildTestSuite(const unsigned int n, ...) {
	CUTE_TestSuite *const ts = malloc(sizeof(CUTE_TestSuite)
	                                  + n * sizeof(CUTE_TestCase*));
	if(ts) {
		va_list args;
		va_start(args, n);
		for(unsigned int i = 0; i < (ts->size = n); ++i) {
			ts->cases[i] = va_arg(args, CUTE_TestCase*);
		}
		va_end(args);
	}
	return ts;
}

void CUTE_destroyTestSuite(CUTE_TestSuite *const ts) {
	free(ts);
}

void CUTE_runTestSuite(const CUTE_TestSuite *const ts) {
	for(unsigned int i = 0; i < ts->size; ++i) {
		CUTE_runTestCase(ts->cases[i]);
	}
}
