#include "cute_test.h"

#include <stdlib.h> /* for malloc, free, NULL */

#include "cute_assert.h" /* for CUTE_assumeValue */



CUTE_RunResults *CUTE_prepareResults(const char *const t,
                                     const unsigned int n) {
	CUTE_RunResults *const r = malloc(sizeof(CUTE_RunResults)
	                                       + n * sizeof(CUTE_TestResult));
	CUTE_assumeValue(r != NULL, NULL);
	r->title = t;
	r->total = n;
	r->successes = 0;
	return r;
}

void CUTE_cleanUpResults(CUTE_RunResults *const r) {
	free(r);
}
