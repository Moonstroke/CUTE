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

#ifndef CUTE_TEST_ALLOW_SUBINCLUDES
#error "This file must not be included directly"
#endif


#define HAVE_OOATTRS /* enable CTOR, MEMBER */
#include <PUCA/funcattrs.h> /* for NOTNULL, CTOR, MEMBER */
#include <stdbool.h> /* for bool, true, false */



/** Represents the status of an executed test. */
typedef enum {
	CUTE_STATUS_SUCCESS,  /**< The test succeeded. */
	CUTE_STATUS_FAILURE,  /**< An assertion failed in the test. */
	CUTE_STATUS_ERROR,    /**< An error occurred during execution. */
	CUTE_STATUS_IGNORED,  /**< The test was not run. */
	CUTE_STATUS_SKIPPED,  /**< The execution of the test was stopped. */
	CUTE_STATUS_CANCELED  /**< The whole test case was stopped. */
} CUTE_TestStatus;


/** The info about the execution of a test. */
typedef struct {
	/** The name of the test executed. */
	const char *name;

	/**
	 * \brief The time, in seconds, elapsed during execution of the test.
	 *
	 * \note This represents the CPU time (time during which the test was
	 *       processed) and not the actual execution time.
	 */
	double time;

	/** The status of the test. */
	CUTE_TestStatus status;

	/** Extra information about the test status. */
	int extra;
} CUTE_TestResult;


/**
 * \brief The info about all the tests after the execution of a test case.
 */
typedef struct {
	const char *title;         /**< The title of the test case. */
	unsigned int total;        /**< The total number of tests run. */
	unsigned int successes;    /**< The number of tests that passed. */
	CUTE_TestResult results[]; /**< The results of the tests. */
} CUTE_RunResults;

/**
 * \brief Allocates a large enough instance of \a CUTE_RunResults.
 *
 * \param[in] title The title of the test case to run
 * \param[in] number The number of tests to prepare the instance for
 *
 * \return An instance of \a CUTE_RunResults for \a number tests.
 */
CTOR CUTE_RunResults *CUTE_prepareResults(const char *title,
                                          unsigned int number)
NOTNULL(1);

/**
 * \brief Deallocates the result of a test case.
 *
 * \param[in,out] results The results to clean up.
 */
MEMBER void CUTE_cleanUpResults(CUTE_RunResults *results);


#include <PUCA/end.h>
