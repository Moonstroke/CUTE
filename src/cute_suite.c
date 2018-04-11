#include "cute_test.h"

#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free */

#include "cute_assert.h" /* for CUTE_assumeValue */



struct testsuite {
	unsigned int number;
	char _padding[4];
	CUTE_TestCase **cases;
	CUTE_RunResults **results;
};
struct testsuite *_suite = NULL;

bool CUTE_prepareTestSuite(const unsigned int n, ...) {
	_suite = malloc(sizeof(struct testsuite));
	CUTE_assumeValue(_suite != NULL, false);
	_suite->cases = calloc(n, sizeof(CUTE_TestCase*));
	CUTE_assumeValue(_suite->cases != NULL, false);
	_suite->results = calloc(n, sizeof(CUTE_RunResults*));
	CUTE_assumeValue(_suite->results != NULL, false);
	va_list args;
	va_start(args, n);
	for(unsigned int i = 0; i < (_suite->number = n); ++i) {
		_suite->cases[i] = va_arg(args, CUTE_TestCase*);
	}
	va_end(args);
	return true;
}

void CUTE_cleanUpTestSuite(void) {
	for(unsigned int i = 0; i < _suite->number; ++i) {
		CUTE_freeTestCase(_suite->cases[i]);
		CUTE_cleanUpResults(_suite->results[i]);
	}
	free(_suite->cases);
	free(_suite->results);
	free(_suite);
}

CUTE_RunResults **CUTE_runTestSuite(void) {
	for(unsigned int i = 0; i < _suite->number; ++i) {
		_suite->results[i] = CUTE_runTestCase(_suite->cases[i]);
	}
	return _suite->results;
}
