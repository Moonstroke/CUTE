#include "cute.h"

#include <stdio.h> /* for fputs, stderr */
#include <stdlib.h> /* for abort */
#include <string.h> /* for strlen */



static void init(void);
static void term(void);
static void setUp(void);
static void tearDown(void);

static void test_1__f(void);
static void test_2__f(void);
static void test_assert__f(void);
static void test_abort__f(void);
static void test_segfault__f(void);


int main(void) {
	CUTE_TestSuite *suite;
	CUTE_TestCase *case_1, *case_2;
	CUTE_Test test_1, test_2, test_assert, test_exit, test_segfault;

	test_1 = CUTE_makeTest(test_1__f);
	test_2 = CUTE_makeTest(test_2__f);
	test_assert = CUTE_makeTest(test_assert__f);
	test_exit = CUTE_makeTest(test_abort__f);
	test_segfault = CUTE_makeTest(test_segfault__f);

	case_1 = CUTE_newTestCase(2);
	CUTE_setCaseInitiate(case_1, init);
	CUTE_setCaseTerminate(case_1, term);
	CUTE_setCaseBefore(case_1, setUp);
	CUTE_setCaseAfter(case_1, tearDown);
	CUTE_addCaseTest(case_1, test_1);
	CUTE_addCaseTest(case_1, test_exit);

	case_2 = CUTE_newTestCase(3);
	CUTE_setCaseInitiate(case_2, init);
	CUTE_setCaseTerminate(case_2, term);
	CUTE_setCaseBefore(case_2, setUp);
	CUTE_setCaseAfter(case_2, tearDown);
	CUTE_addCaseTest(case_2, test_2);
	CUTE_addCaseTest(case_2, test_assert);
	CUTE_addCaseTest(case_2, test_segfault);

	suite = CUTE_buildTestSuite(2, case_1, case_2);

	CUTE_runTestSuite(suite);


	CUTE_destroyTestSuite(suite);
	return 0;
}

void init(void) {
	fputs("init\n", stderr);
}
void term(void) {
	fputs("term\n", stderr);
}

void setUp(void) {
	fputs("setUp\n", stderr);
}
void tearDown(void) {
	fputs("tearDown\n\n", stderr);
}


void test_1__f(void) {
	fputs("test 1 called\n", stderr);
}
void test_2__f(void) {
	fputs("test 2 called\n", stderr);
}

void test_assert__f(void) {
	fputs("failing assertion\n", stderr);
	CUTE_assertEquals(1, 2);
}
void test_abort__f(void) {
	fputs("call abort()\n", stderr);
	abort();
}
void test_segfault__f(void) {
	fputs("trigger segmentation fault\n", stderr);
	"string"[8] = '/';
}
