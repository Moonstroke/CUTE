#ifndef CUTE_H
#define CUTE_H


#ifndef __GNUC__
#define __attribute__(x)
#endif

#define CUTE_INLINE __attribute__((__always_inline__)) inline

#define CUTE_PURE __attribute__((__pure__, __warn_unused_result__))

#define CUTE_NOTNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))


#define CUTE_NULL_GUARD(i) __attribute__((__sentinel__(i)))
#define CUTE_LAST_ARG_NULL CUTE_NULL_GUARD(0)


#define CUTE_CTOR __attribute__((__malloc__))

#define CUTE_MEMBER CUTE_NOTNULL(1)


#endif /* CUTE_H */
