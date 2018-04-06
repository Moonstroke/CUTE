#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif



typedef enum {
	CUTE_RESULT_SUCCESS,
	CUTE_RESULT_FAILURE,
	CUTE_RESULT_ERROR,
	CUTE_RESULT_IGNORED,
	CUTE_RESULT_SKIPPED,
	CUTE_RESULT_CANCELED
} CUTE_TestStatus;


typedef struct {
	const char *name;
	CUTE_TestStatus result;
	int extra;
} CUTE_TestResult;


typedef struct {
	unsigned int total, successes;
	CUTE_TestResult results[];
} CUTE_TestCaseOutcome;

CUTE_CTOR CUTE_TestCaseOutcome *CUTE_prepareOutcome(unsigned int number);

CUTE_MEMBER void CUTE_cleanUpOutcome(CUTE_TestCaseOutcome *outcome);
