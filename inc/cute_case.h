#ifndef CUTE_TEST_H
#error "This file must not be included directly, please include cute_test.h instead"
#endif


#include <stdbool.h> /* for bool, true, false */

#include "cute_test.h"



typedef struct testcase CUTE_TestCase;


CUTE_CTOR CUTE_TestCase *CUTE_newTestCase(unsigned int number);
CUTE_MEMBER void CUTE_freeTestCase(CUTE_TestCase *case_);

CUTE_MEMBER void CUTE_setCaseInitiate(CUTE_TestCase *case_, CUTE_Proc *initiate);
CUTE_MEMBER void CUTE_setCaseTerminate(CUTE_TestCase *case_, CUTE_Proc *terminate);

CUTE_MEMBER void CUTE_setCaseBefore(CUTE_TestCase *case_, CUTE_Proc *setUp);
CUTE_MEMBER void CUTE_setCaseAfter(CUTE_TestCase *case_, CUTE_Proc *tearDown);

CUTE_MEMBER bool CUTE_addCaseTest(CUTE_TestCase *case_, CUTE_Test test);

CUTE_MEMBER void CUTE_runTestCase(CUTE_TestCase *case_);
