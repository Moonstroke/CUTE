#include "cute_test.h"

#include <stdarg.h> /* for va_* */
#include <stdlib.h> /* for malloc, free, exit, EXIT_* */

#include "cute_assert.h" /* for CUTE_assumeValue */



struct testsuite {
	unsigned int number;
	int status; /* = EXIT_SUCCESS or EXIT_FAILURE */
	CUTE_TestCase **cases;
	CUTE_RunResults **results;
};
static struct testsuite _suite = {0};

bool CUTE_prepareTestSuite(const unsigned int n, ...) {
	_suite.cases = calloc(n, sizeof(CUTE_TestCase*));
	CUTE_assumeValue(_suite.cases != NULL, false);
	_suite.results = calloc(n, sizeof(CUTE_RunResults*));
	CUTE_assumeValue(_suite.results != NULL, false);
	va_list args;
	va_start(args, n);
	for(unsigned int i = 0; i < (_suite.number = n); ++i) {
		_suite.cases[i] = va_arg(args, CUTE_TestCase*);
	}
	va_end(args);
	return true;
}

void CUTE_cleanUpTestSuite(void) {
	for(unsigned int i = 0; i < _suite.number; ++i) {
		CUTE_freeTestCase(_suite.cases[i]);
		CUTE_cleanUpResults(_suite.results[i]);
	}
	free(_suite.cases);
	free(_suite.results);
}

const CUTE_RunResults **CUTE_runTestSuite(void) {
	for(unsigned int i = 0; i < _suite.number; ++i) {
		_suite.results[i] = CUTE_runTestCase(_suite.cases[i]);
		/* set appropriate value for the exit status */
		if(_suite.status == EXIT_SUCCESS
		   && _suite.results[i]->successes != _suite.results[i]->total) {
			_suite.status = EXIT_FAILURE;
		}
	}
	return (const CUTE_RunResults**)_suite.results;
}

/* declared in cute_test.h */
void CUTE_exit(void) {
	exit(_suite.status);
}
