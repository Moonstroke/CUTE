#include "cute_test.h"

#include <stdlib.h>



CUTE_TestCaseOutcome *CUTE_prepareOutcome(const unsigned int n) {
	CUTE_TestCaseOutcome *const o = malloc(sizeof(CUTE_TestCaseOutcome)
	                                       + n * sizeof(CUTE_TestResult));
	if(o) {
		o->total = n;
		o->successes = 0;
	}
	return o;
}

void CUTE_cleanUpOutcome(CUTE_TestCaseOutcome *const o) {
	free(o);
}
