/**
 * \file "cute_result.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Structures and function to store and manipulate test results.
 *
 * The enumeration \a CUTE_TestStatus declares constants that represent the
 * status of the test after its execution: it can be a success, a failure (an
 * assertion did not pass), an error (any other error, e.g. a floating-point
 * error); the test can also have been ignored (the name starts with the
 * uppercase \c I character), skipped (Ctrl-Z in terminal) or canceled (Ctrl-C
 * or Ctrl-\\) by the user.
 *
 * Several structures are defined in this file:
 * - \a CUTE_TestResult contains the result of the executuon of one test: the
 *   name of the test, and its result. It also contain an extra field that may
 *   be used for supplementary info, and
 * - CUTE_RunResults, that contains the results of the running of an entire test
 *   case, the number of tests run, and the number of tests that succeeded.
 */

#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif



/**
 * \brief Represents the status of an executed test.
 */
typedef enum {
	CUTE_STATUS_SUCCESS,
	CUTE_STATUS_FAILURE,
	CUTE_STATUS_ERROR,
	CUTE_STATUS_IGNORED,
	CUTE_STATUS_SKIPPED,
	CUTE_STATUS_CANCELED
} CUTE_TestStatus;


/**
 * \brief The info about the execution of a test.
 */
typedef struct {
	/**
	 * \brief The name of the test executed.
	 */
	const char *name;

	/**
	 * \brief The status of the test.
	 */
	CUTE_TestStatus status;

	/**
	 * \brief Extra information about the test status.
	 */
	int extra;
} CUTE_TestResult;


/**
 * \brief The info about all the tests after the execution of a test case.
 */
typedef struct {
	/**
	 * \brief The total number of tests run.
	 */
	unsigned int total;

	/**
	 * \brief The number of tests that passed.
	 */
	unsigned int successes;

	/**
	 * \brief The results of the tests.
	 */
	CUTE_TestResult results[];
} CUTE_RunResults;

/**
 * \brief Allocates a large enough instance of \a CUTE_RunResults.
 *
 * \param[in] number The number of tests to prepare the instance for.
 *
 * \return An instance of \a CUTE_RunResults for \a number tests.
 */
CUTE_CTOR CUTE_RunResults *CUTE_prepareResults(unsigned int number);

/**
 * \brief Deallocates the result of a test case.
 *
 * \param[in,out] results The results to clean up.
 */
CUTE_MEMBER void CUTE_cleanUpResults(CUTE_RunResults *results);
