/**
 * \file "cute_assert.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Assertions macros.
 *
 * This file defines macros to ensure that a condition is \c true.
 * If the condition is \c false, the program execution ends with an \a abort
 * call.
 * If the macro \c NDEBUG is defined, assertions are not executed.
 */
#ifndef CUTE_ASSERT_H
#define CUTE_ASSERT_H


#include <assert.h> /* for assert, static_assert */
#include <string.h> /* for strcmp */

#include "cute.h"



/**
 * \brief Aborts if the condition evaluates to \c 0.
 *
 * \note This merely is a redefinition of the standard macro \a assert.
 *
 * \param[in] cond The expression to evaluate
 */
#define CUTE_runTimeAssert(cond) assert(cond)

/**
 * \brief Evaluates the expression during compilation.
 *
 * \param[in] cond The expression to evaluates
 * \param[in] msg The message to output if the evaluation fails
 */
#define CUTE_compileTimeAssert(cond, msg) static_assert(cond, msg)


/**
 * \brief Ensures that the given values are equal.
 *
 * \param[in] x The first value
 * \param[in] y The second value
 */
#define CUTE_assertEquals(x, y) CUTE_runTimeAssert((x) == (y))

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

#endif /* CUTE_ASSERT_H */
