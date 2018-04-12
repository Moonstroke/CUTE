/**
 * \file "cute_suite.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Defines an internal structure to run several test cases.
 *
 * This structure is called a test suite, it is used to run simultaneously
 * several test cases at once. It is only used internally and is not accessible
 * to the programmer as only one instance will ever exist at once.
 *
 * \note This file can not be included directly, it is automatically provided
 *       when \c cute_test.h is included.
 */
#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif


#include <stdbool.h> /* for bool, true, false */



/**
 * \brief Constructs the test suite from the given test cases.
 *
 * \note This variadic function assumes to receive \a size variadic arguments of
 *       type \c CUTE_TestCase*.
 *
 * \param[in] size The number of test cases
 * \param[in] ...  The test cases to include in the suite
 *
 * \return \c true if the allocation happened nominally.
 */
bool CUTE_prepareTestSuite(unsigned int size, ...);

/**
 * \brief Deallocates the test suite.
 *
 * \note The test cases included in the suite are also freed.
 */
void CUTE_cleanUpTestSuite(void);

/**
 * \brief Runs the test suite.
 *
 * \return An array containing the results of the execution of the tests
 */
const CUTE_RunResults **CUTE_runTestSuite(void);
