#include "cute_test.h"

#include <stdlib.h>



CUTE_RunResults *CUTE_prepareResults(const unsigned int n) {
	CUTE_RunResults *const r = malloc(sizeof(CUTE_RunResults)
	                                       + n * sizeof(CUTE_TestResult));
	if(r) {
		r->total = n;
		r->successes = 0;
	}
	return r;
}

void CUTE_cleanUpResults(CUTE_RunResults *const r) {
	free(r);
}
