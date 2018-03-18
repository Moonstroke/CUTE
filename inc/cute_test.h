#ifndef CUTE_TEST_H
#define CUTE_TEST_H


#include "cute.h"


typedef void (CUTE_Proc)(void);

typedef struct {
	CUTE_Proc *proc;
	const char *name;
} CUTE_Test;


#define CUTE_makeTest(proc) (CUTE_Test){proc, #proc}

#define CUTE_getTestName(test) test->name

#define CUTE_runTest(test) test->proc()


#endif /* CUTE_TEST_H */
