/**
 * \file "cute_assert.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Assertions macros.
 *
 * This file defines macros to ensure that a condition is \c true.
 * If the condition is \c false, the program execution ends with an \a abort(3)
 * call.
 * If the macro \c NDEBUG is defined, assertions are not executed.
 */
#ifndef CUTE_ASSERT_H
#define CUTE_ASSERT_H


#include <string.h> /* for strcmp */
#include <errno.h> /* for E* */

#include "cute.h"


/**
 * \defgroup assertions Assertions macros
 * \{
 */

/**
 * \def CUTE_runTimeAssert
 *
 * \brief Aborts if the condition evaluates to \c 0.
 *
 * \note This merely is a redefinition of the standard macro \a assert(3).
 *
 * \param[in] cond The expression to evaluate
 */
#if defined(NDEBUG)
# define CUTE_runTimeAssert(cond) (void)(cond)
#else
# define CUTE_runTimeAssert(cond)\
	if(cond); else CUTE_fail("Assertion " #cond " failed", __FILE__, __LINE__,\
	                         __func__)
#endif


/**
 * \def CUTE_compileTimeAssert
 *
 * \brief Evaluates the expression during compilation.
 *
 * \note With pre-11 C, this macro is defined with a hacky syntax. In this case,
 *       the macro can not be used at global scope.
 *
 * \param[in] cond The expression to evaluates
 * \param[in] msg The message to output if the evaluation fails
 */
#if __STDC_VERSION__ >= 201112L /* C11 introduced the _Static_assert feature */
# define CUTE_compileTimeAssert(cond, msg) _Static_assert(cond, msg)
#else  /* dirty hack for pre-C11 C */
# define CUTE_compileTimeAssert(cond, msg) do { int _[cond ? -1 : 1]; } while(0)
#endif


/**
 * \brief Ensures that the given values are equal.
 *
 * \param[in] x The first value
 * \param[in] y The second value
 */
#define CUTE_assertEquals(x, y) CUTE_runTimeAssert((x) == (y))

/**
 * \brief Ensures that the two values are not equal.
 *
 * \param[in] x The first value
 * \param[in] y The second value
 */
#define CUTE_assertNotEquals(x, y) CUTE_runTimeAssert((x) != (y))

/**
 * \brief Ensures that the given values compare to a result value with the given
 *        function.
 * \param[in] x    The first value to test
 * \param[in] y    The second value
 * \param[in] func The function to compare with
 * \param[in] ok   The expected return value
 */
#define CUTE_assertEqualsUsing(x, y, func, ok) \
	CUTE_runTimeAssert(func((x), (y)) == (ok))

/**
 * \brief Compares two string values.
 *
 * \param[in] s1 The first string
 * \param[in] s2 The second string
 */
#define CUTE_assertStringEquals(s1, s2) \
	CUTE_assertEqualsWith((s1), (s2), strcmp, 0)


/**
 * Ensures that \c errno matches the given error code.
 *
 * \param[in] errcode The error code to check
 */
#define CUTE_assertErrnoEquals(errcode) CUTE_assertEquals(errno, errcode)


/** \brief Ensures that no error code is set. */
#define CUTE_assertNoError() CUTE_assertErrnoEquals(0)


/**
 * \brief Fails immediately by raising the \c SIGABRT signal.
 *
 * \note If \a msg is \c NULL no output is written on \e stderr.
 *
 * \param[in] msg  A message to print
 * \param[in] file The file where the call was made from (use \c __FILE__)
 * \param[in] line The line number in the file (use \c __LINE__)
 * \param[in] func The function within which the call was made (use \c __func__)
 */
void CUTE_fail(const char *msg, const char *file, unsigned int line,
               const char *func);

/** \} */


/**
 * \brief Ends the function immediately if a condition is not met.
 *
 * \note Unlike \a CUTE_runTimeAssert, this macro does not result in an error;
 *       it only returns from the function quietly.
 *
 * \param[in] cond The condition to check
 */
#define CUTE_assume(cond) if(cond); else return;


/**
 * \brief Returns immediately the given value if a condition is not met.
 *
 * \note Use this to \e assume a condition from a non-\c void function.
 *
 * \param[in] cond  The condition to check
 * \param[in] value The value to return
 */
#define CUTE_assumeValue(cond, value) if(cond); else return value;


#endif /* CUTE_ASSERT_H */
