#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif



typedef enum {
	CUTE_STATUS_SUCCESS,
	CUTE_STATUS_FAILURE,
	CUTE_STATUS_ERROR,
	CUTE_STATUS_IGNORED,
	CUTE_STATUS_SKIPPED,
	CUTE_STATUS_CANCELED
} CUTE_TestStatus;


typedef struct {
	const char *name;
	CUTE_TestStatus result;
	int extra;
} CUTE_TestResult;


typedef struct {
	unsigned int total, successes;
	CUTE_TestResult results[];
} CUTE_RunResults;

CUTE_CTOR CUTE_RunResults *CUTE_prepareResults(unsigned int number);

CUTE_MEMBER void CUTE_cleanUpResults(CUTE_RunResults *results);
