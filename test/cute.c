#include "cute.h"

#include <clog.h>
#include <signal.h> /* for raise, SIGINT, SIGQUIT, SIGABRT, SIGTSTP */
#include <stdlib.h> /* for free, EXIT_SUCCESS */



static void init(void);
static void term(void);
static void setUp(void);
static void tearDown(void);

static void test_1__f(void);
static void test_2__f(void);
static void test_assert__f(void);
static void test_abort__f(void);
static void test_interrupt__f(void);
static void test_quit__f(void);
static void test_tstop__f(void);
static void Itest_ignored__f(void);


int main(void) {

	clog_init(CLOG_FORMAT_TEXT, CLOG_ATTR_COLORED);

	CUTE_TestCase *case_1, *case_2;
	CUTE_Test test_1,
	          test_2,
	          test_assert,
	          test_abort,
	          test_interrupt,
	          test_quit,
	          test_tstop,
	          test_ignored;
	const CUTE_RunResults **results;

	test_1 = CUTE_makeTest(test_1__f);
	test_2 = CUTE_makeTest(test_2__f);
	test_assert = CUTE_makeTest(test_assert__f);
	test_abort = CUTE_makeTest(test_abort__f);
	test_interrupt = CUTE_makeTest(test_interrupt__f);
	test_quit = CUTE_makeTest(test_quit__f);
	test_tstop = CUTE_makeTest(test_tstop__f);
	test_ignored = CUTE_makeTest(Itest_ignored__f);

	case_1 = CUTE_newTestCase("case 1", 4);
	CUTE_setCaseInitiate(case_1, init);
	CUTE_setCaseTerminate(case_1, term);
	CUTE_setCaseBefore(case_1, setUp);
	CUTE_setCaseAfter(case_1, tearDown);
	CUTE_addCaseTest(case_1, test_1);
	CUTE_addCaseTest(case_1, test_abort);
	CUTE_addCaseTest(case_1, test_tstop);
	CUTE_addCaseTest(case_1, test_quit);

	case_2 = CUTE_newTestCase("case 2", 4);
	CUTE_setCaseInitiate(case_2, init);
	CUTE_setCaseTerminate(case_2, term);
	CUTE_setCaseBefore(case_2, setUp);
	CUTE_setCaseAfter(case_2, tearDown);
	CUTE_addCaseTest(case_2, test_2);
	CUTE_addCaseTest(case_2, test_assert);
	CUTE_addCaseTest(case_2, test_ignored);
	CUTE_addCaseTest(case_2, test_interrupt);

	CUTE_prepareTestSuite(2, case_1, case_2);

	results = CUTE_runTestSuite();

	info("console output");
	CUTE_printResults(2, results);
	info("simple text output");
	CUTE_logResults(2, results, stderr, CUTE_FORMAT_TEXT);
	info("XML output");
	CUTE_logResults(2, results, stderr, CUTE_FORMAT_XML);


	CUTE_cleanUpTestSuite();
	return EXIT_SUCCESS;
}

void init(void) {
	verbose("init");
}
void term(void) {
	verbose("term\n");
}

void setUp(void) {
	verbose("setUp");
}
void tearDown(void) {
	verbose("tearDown");
}


void test_1__f(void) {
	info("test 1 called");
}
void test_2__f(void) {
	info("test 2 called");
}

void test_assert__f(void) {
	info("failing assertion");
	CUTE_assertEquals(1, 2);
	error("This text should not be printed!");
}
void test_abort__f(void) {
	info("raise SIGABRT");
	raise(SIGABRT);
	error("This text should not be printed!");
}
void test_interrupt__f(void) {
	info("interrupt (Ctrl-C)");
	raise(SIGINT);
	error("This text should not be printed!");
}
void test_quit__f(void) {
	info("quit (Ctrl-\\)");
	raise(SIGQUIT);
	error("This text should not be printed!");
}
void test_tstop__f(void) {
	info("TTY stop (Ctrl-Z)");
	raise(SIGTSTP);
	error("This text should not be printed!");
}
void Itest_ignored__f(void) {
	error("This text should not be printed!");
}
