#include "cute_assert.h"

#include <stdio.h> /* for fputs, stderr */
#include <stdlib.h> /* for abort */



void CUTE_fail(const char *const msg, const char *const file,
               const unsigned int line, const char *const func) {
	fprintf(stderr, "%s:%u, %s(): %s\n", file, line, func, msg);
	abort();
}
