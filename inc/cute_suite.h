/**
 * \file "cute_suite.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Defines a structure to run several test cases.
 *
 * This structure is a test suite, it is used to run simultaneously several test
 * cases at once.
 *
 * \note This file can not be included directly, it is automatically provided
 *       when \c cute_test.h is included.
 */
#ifndef CUTE_TEST_H
#error "This file must not be included directly, please include cute_test.h instead"
#endif



/**
 * \brief An opaque definition of the test suite.
 */
typedef struct testsuite CUTE_TestSuite;


/**
 * \brief Constructs a test suite from the given test cases.
 *
 * \note This variadic function assumes to receive \a size variadic arguments of
 *       type \c CUTE_TestCase*.
 *
 * \param[in] size The number of test cases
 * \param[in] ...  The test cases to include in the suite
 *
 * \return A test suite consisting of the \a size given test cases.
 */
CUTE_CTOR CUTE_TestSuite *CUTE_buildTestSuite(unsigned int size, ...);

/**
 * \brief Deallocates a test suite.
 *
 * \note The test cases included in the suite are also freed.
 *
 * \param[in] s The test suite
 */
void CUTE_destroyTestSuite(CUTE_TestSuite *s);

/**
 * \brief Runs the test suite.
 *
 * \param[in] suite The test suite
 */
void CUTE_runTestSuite(const CUTE_TestSuite *suite);
