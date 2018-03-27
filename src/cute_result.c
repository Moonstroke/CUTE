#include "cute_test.h"

#include <stdlib.h>



void CUTE_prepareOutcome(CUTE_TestCaseOutcome **const o,
                         const unsigned int n) {
	CUTE_TestCaseOutcome *const _o = malloc(sizeof(CUTE_TestCaseOutcome)
	                                        + n * sizeof(CUTE_TestResult));
	if(_o) {
		_o->total = n;
		_o->successes = 0;
	}
	*o = _o;
}

void CUTE_cleanUpOutcome(CUTE_TestCaseOutcome *const o) {
	free(o);
}
