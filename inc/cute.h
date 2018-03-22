/**
 * \file cute.h
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
/**
 * \brief Empty declaration for non-GNU C.
 */
#define __attribute__(x)
#endif

/**
 * \brief The function is inlined everywhere it is met.
 */
#define CUTE_INLINE __attribute__((__always_inline__)) inline

/**
 * \brief The function does not affect external data.
 */
#define CUTE_PURE __attribute__((__pure__, __warn_unused_result__))

/**
 * \brief The arguments to the function given here must not be \c NULL.
 *
 * \param[in] ... The indices of the arguments that must not be \c NULL.
 */
#define CUTE_NOTNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))

/**
 * \brief The argument at given index, counting backwards, must be \c NULL.
 *
 * \note This attribute is only to be used on variadic functions.
 *
 * \param i The index
 */
#define CUTE_NULL_GUARD(i) __attribute__((__sentinel__(i)))

/**
 * \brief The last argument of the function \i must be an explicit \c NULL.
 *
 * \note As for \a CUTE_NULL_GUARD, this attribute is only valid on variadic
 *       functions.
 */
#define CUTE_LAST_ARG_NULL CUTE_NULL_GUARD(0)

/**
 * \brief The function allocates memory on the heap.
 */
#define CUTE_CTOR __attribute__((__malloc__))

/**
 * \brief The function is related to a OO-like data type.
 *
 * \note The meaning of this attribute is purely semantic; it actually only
 *       ensures that the first argument, the type instance pointer, is not
 *       \c NULL.
 */
#define CUTE_MEMBER CUTE_NOTNULL(1)



#if !defined(CUTE_TEST_H) && !defined(CUTE_ASSERT_H)
#include "cute_assert.h"
#include "cute_test.h"
#endif


#endif /* CUTE_H */
