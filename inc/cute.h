/**
 * \file "cute.h"
 * \author joH1
 * \version 0.1
 *
 * \brief The main header of the project.
 *
 * This file serves two purposes: it contains common features used by the files
 * of the project (like function attributes), and it can be used to include the
 * whole project at once.
 */
#ifndef CUTE_H
#define CUTE_H


#ifndef __GNUC__
# define __attribute__(x) /**< Empty declaration for non-GNU C. */
#endif

/**
 * \defgroup funcattrs Function attributes
 * \{
 */

/** The function is inlined everywhere it is met. */
#define CUTE_INLINE __attribute__((__always_inline__)) inline

/** The function does not affect external data. */
#define CUTE_PURE __attribute__((__pure__, __warn_unused_result__))

/**
 * \brief The arguments to the function given here must not be \c NULL.
 *
 * \param[in] ... The indices of the arguments that must not be \c NULL.
 */
#define CUTE_NOTNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))

/** The function allocates memory on the heap. */
#define CUTE_CTOR __attribute__((__malloc__))

/**
 * \brief The function is related to a OO-like data type.
 *
 * \note The meaning of this attribute is purely semantic; in reality, it only
 *       ensures that the first argument, the instance pointer, is not \c NULL.
 */
#define CUTE_MEMBER CUTE_NOTNULL(1)

/** \} */


#if !defined(CUTE_TEST_H) && !defined(CUTE_ASSERT_H)
#include "cute_assert.h"
#include "cute_test.h"
#endif


#endif /* CUTE_H */
