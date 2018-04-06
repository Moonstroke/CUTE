#include "cute_assert.h"

#include <stdio.h> /* for fputs, stderr */
#include <signal.h> /* for raise, SIGABRT */



void CUTE_fail(const char *const msg, const char *const file,
               const unsigned int line, const char *const func) {
	if(msg) fprintf(stderr, "%s:%u, %s(): %s\n", file, line, func, msg);
	raise(SIGABRT);
}
