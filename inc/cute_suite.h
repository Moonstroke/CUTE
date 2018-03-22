#ifndef CUTE_TEST_H
#error "This file must not be included directly, please include cute_test.h instead"
#endif


#include "cute.h"



typedef struct testsuite CUTE_TestSuite;


CUTE_CTOR CUTE_TestSuite *CUTE_buildTestSuite(unsigned int size, ...);

void CUTE_destroyTestSuite(CUTE_TestSuite *s);

void CUTE_runTestSuite(const CUTE_TestSuite *suite);
