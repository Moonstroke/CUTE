/**
 * \file "cute_case.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Defines a a test case structure.
 *
 * A test case is a structure designed to contain several tests semantically
 * related, like different tests on the same function, or the same type.
 * A test case has a title that illustrates the feature being tested.
 *
 * \note This file can not be included directly, it is automatically provided
 *       when \c cute_test.h is included.
 */
#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif


#include <stdbool.h> /* for bool, true, false */



/** A set of coherent tests. */
typedef struct {
	const char *title;     /**< The title of the case. */
	CUTE_Proc *initiate;   /**< The procedure to call before all tests. */
	CUTE_Proc *terminate;  /**< The procedure to call after all tests. */
	CUTE_Proc *before;     /**< The procedure to call before each test. */
	CUTE_Proc *after;      /**< The procedure to call after each test. */
	unsigned int capacity; /**< The maximum number of tests to contain. */
	unsigned int number;   /**< The number of tests actually in the case. */
	CUTE_Test tests[];     /**< The tests. */
} CUTE_TestCase;


/**
 * \brief Instantiates a test case for a specified number of unit tests.
 *
 * \note At the moment of execution, the case is expected to contain exactly
 * \a number elements.
 *
 * \param[in] title The title of the test case
 * \param[in] number The number of unit tests
 *
 * \return A new test case ready to hold \a number tests.
 */
CUTE_CTOR CUTE_TestCase *CUTE_newTestCase(const char *title,
                                          unsigned int number) CUTE_NOTNULL(1);

/**
 * \brief Release the memory from a test case.
 *
 * \param[in,out] case_ The test case to deallocate
 */
CUTE_MEMBER void CUTE_freeTestCase(CUTE_TestCase *case_);


/**
 * \brief Specifies the procedure to call before running the tests.
 *
 * \param[in,out] case_    The test case
 * \param[in]     initiate The procedure
 */
CUTE_MEMBER CUTE_INLINE CUTE_NOTNULL(2)
void CUTE_setCaseInitiate(CUTE_TestCase *const case_,
                          CUTE_Proc *const initiate) {
	case_->initiate = initiate;
}

/**
 * \brief Specifies the procedure to call after having run all the tests.
 *
 * \param[in,out] case_     The test case
 * \param[in]     terminate The procedure
 */
CUTE_MEMBER CUTE_INLINE CUTE_NOTNULL(2)
void CUTE_setCaseTerminate(CUTE_TestCase *const case_,
                           CUTE_Proc *const terminate) {
	case_->terminate = terminate;
}

/**
 * \brief Specifies the procedure to call before every test.
 *
 * \param[in,out] case_ The test case
 * \param[in]     setUp The procedure
 */
CUTE_MEMBER CUTE_INLINE CUTE_NOTNULL(2)
void CUTE_setCaseBefore(CUTE_TestCase *const case_, CUTE_Proc *const setUp) {
	case_->before = setUp;
}

/**
 * \brief Specifies the procedure to call after each test.
 *
 * \param[in,out] case_    The test case
 * \param[in]     tearDown The procedure
 */
CUTE_MEMBER CUTE_INLINE CUTE_NOTNULL(2)
void CUTE_setCaseAfter(CUTE_TestCase *const case_, CUTE_Proc *const tearDown) {
	case_->after = tearDown;
}


/**
 * \brief Adds a unit test to the list of tests in the case.
 *
 * \note The test is only added if there is free space in the tests list of the
 *       case.
 *
 * \param[in,out] case_ The test case
 * \param[in]     test  The unit test
 *
 * \return \c true if the test could be added (there was enough space left in
 *         the test case).
 */
CUTE_MEMBER bool CUTE_addCaseTest(CUTE_TestCase *case_, CUTE_Test test);


/**
 * \brief Retrieves the title of the test case.
 *
 * \param[in] case_ The test case
 *
 * \return The title of the test case.
 */
CUTE_MEMBER CUTE_INLINE CUTE_PURE
const char *CUTE_getCaseTitle(const CUTE_TestCase *case_) {
	return case_->title;
}

/**
 * \brief Retrieves the number of tests in the case.
 *
 * \param[in] case_ The test case
 *
 * \return The number of unit tests in the case.
 */
CUTE_MEMBER CUTE_INLINE CUTE_PURE
unsigned int CUTE_getCaseTestsNumber(const CUTE_TestCase *case_) {
	return case_->number;
}


/**
 * \brief Runs the tests in the case.
 *
 * \note It is not ensured that the tests are executed in the same order as they
 *       were added to the case.
 *
 * \param[in]  case_  The test case
 *
 * \return A pointer to the results of the tests.
 */
CUTE_MEMBER CUTE_RunResults *CUTE_runTestCase(const CUTE_TestCase *case_);
