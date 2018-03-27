/**
 * \file "cute_case.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Defines a a test case structure.
 *
 * A test case is a structure designed to contain several tests semantically
 * related, like different tests on the same function, or the same type.
 *
 * \note This file can not be included directly, it is automatically provided
 *       when \c cute_test.h is included.
 */
#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif


#include <stdbool.h> /* for bool, true, false */



/**
 * \brief Opaque definition for the test case.
 */
typedef struct testcase CUTE_TestCase;


/**
 * \brief Instantiates a test case for a specified number of unit tests.
 *
 * \note At the moment of execution, the case is expected to contain exactly
 * \a number elements.
 *
 * \param[in] number The number of unit tests
 *
 * \return A new test case ready to hold \a number tests.
 */
CUTE_CTOR CUTE_TestCase *CUTE_newTestCase(unsigned int number);

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
CUTE_MEMBER CUTE_NOTNULL(2) void CUTE_setCaseInitiate(CUTE_TestCase *case_,
                                                      CUTE_Proc *initiate);
/**
 * \brief Specifies the procedure to call after having run all the tests.
 *
 * \param[in,out] case_     The test case
 * \param[in]     terminate The procedure
 */
CUTE_MEMBER CUTE_NOTNULL(2) void CUTE_setCaseTerminate(CUTE_TestCase *case_,
                                                       CUTE_Proc *terminate);

/**
 * \brief Specifies the procedure to call before every test.
 *
 * \param[in,out] case_ The test case
 * \param[in]     setUp The procedure
 */
CUTE_MEMBER CUTE_NOTNULL(2) void CUTE_setCaseBefore(CUTE_TestCase *case_,
                                                    CUTE_Proc *setUp);
/**
 * \brief Specifies the procedure to call after each test.
 *
 * \param[in,out] case_    The test case
 * \param[in]     tearDown The procedure
 */
CUTE_MEMBER CUTE_NOTNULL(2) void CUTE_setCaseAfter(CUTE_TestCase *case_,
                                                   CUTE_Proc *tearDown);

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
 * \brief Retrieves the number of tests in the case.
 *
 * \param[in] case_ The test case
 *
 * \return The number of unit tests in the case.
 */
CUTE_MEMBER unsigned int CUTE_getCaseTestsNumber(CUTE_TestCase *case_) CUTE_PURE;


/**
 * \brief Runs the tests in the case.
 *
 * \note It is not ensured that the tests are executed in the same order as they
 *       were added to the case.
 *
 * \param[in] case_ The test case
 */
CUTE_MEMBER void CUTE_runTestCase(const CUTE_TestCase *case_);
