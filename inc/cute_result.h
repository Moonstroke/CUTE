#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif



typedef enum {
	CUTE_RESULT_SUCCESS,
	CUTE_RESULT_FAILURE,
	CUTE_RESULT_ERROR,
	CUTE_RESULT_IGNORED,
	CUTE_RESULT_CANCELED
} CUTE_TestStatus;


typedef struct {
	const char *name;
	CUTE_TestStatus result;
	char padding[4];
} CUTE_TestResult;


typedef struct {
	unsigned int total, successes;
	CUTE_TestResult results[];
} CUTE_TestCaseOutcome;

void CUTE_prepareOutcome(CUTE_TestCaseOutcome **outcome,
                         unsigned int number) CUTE_NOTNULL(1);

void CUTE_cleanUpOutcome(CUTE_TestCaseOutcome *outcome) CUTE_NOTNULL(1);
