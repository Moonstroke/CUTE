/**
 * \file "cute_test.h"
 * \author joH1
 * \version 0.1
 *
 * \brief Unit tests macros.
 *
 * This file defines the \a CUTE_Test structure and macros to manipulate it.
 * It also includes the headers \c cute_case.h and \c cute_suite.h
 */
#ifndef CUTE_TEST_H
#define CUTE_TEST_H


#include "cute.h"



/**
 * \brief A convenient type definition for a 0-parameter procedure.
 *
 * This is the profile of all the functions passed to the system: tests, helper
 * functions (\c setUp, \c tearDown).
 */
typedef void (CUTE_Proc)(void);

/**
 * \brief This structure represents a single unit test.
 */
typedef struct {
	/** \brief The actual procedure to run. */
	CUTE_Proc *proc;
	/** \brief The name of the test procedure. */
	const char *name;
} CUTE_Test;


/**
 * \brief Wraps a procedure in a unit test structure.
 *
 * \param[in] proc The procedure
 *
 * \return A \a CUTE_Test of the given procedure.
 */
#define CUTE_makeTest(proc) (CUTE_Test){proc, #proc}

/**
 * \brief Returns the name of the test.
 *
 * \param[in] test The test
 *
 * \return The \a name member of the test instance.
 */
#define CUTE_getTestName(test) (test).name

/**
 * \brief Runs the test procedure.
 *
 * \param[in] test The test to run
 */
#define CUTE_runTest(test) (test).proc()


/**
 * Exits the program with the appropriate status (\c EXIT_SUCCESS if all tests
 * run passed, \c EXIT_FAILURE otherwise).
 */
CUTE_NORETURN void CUTE_exit(void);


/** Internal flag to allow inclusion of sub-headers, do not use. */
#define CUTE_TEST_ALLOW_SUBINCLUDES

#include "cute_result.h"
#include "cute_case.h"
#include "cute_suite.h"
#include "cute_log.h"
#undef CUTE_TEST_ALLOW_SUBINCLUDES


#endif /* CUTE_TEST_H */
