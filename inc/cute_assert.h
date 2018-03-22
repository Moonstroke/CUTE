#ifndef CUTE_ASSERT_H
#define CUTE_ASSERT_H


#include <assert.h> /* for assert, static_assert */
#include <string.h> /* for strcmp */

#include "cute.h"



#define CUTE_runTimeAssert(cond) assert(cond)
#define CUTE_compileTimeAssert(cond, msg) static_assert(cond, msg)


#define CUTE_assertEquals(x, y) CUTE_runTimeAssert((x) == (y))

#define CUTE_assertEqualsUsing(x, y, func, ok) \
	CUTE_runTimeAssert(func((x), (y)) == (ok))

#define CUTE_assertStringEquals(s1, s2) \
	CUTE_assertEqualsWith((s1), (s2), strcmp, 0)

#endif /* CUTE_ASSERT_H */
