/**
 * \file "cute_log.h"
 * \author joH1
 * \version 0.1
 *
 * \brief A system to log test results.
 *
 * Ths file defines a simple results logger. An output file can be specified, as
 * well as an output format from within the \c enum \a CUTE_LogFormat.
 */

#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif


#include <stdio.h> /* for FILE */

#include "cute_test.h"



/**
 * \brief Represents the format in which output the results.
 */
typedef enum {
	/**
	 * \brief Output the results as simple text.
	 */
	CUTE_FORMAT_TEXT,

	/**
	 * \brief Output the results as XML.
	 *
	 * \note The file \c cute.dtd contains the description of the structure used
	 *       to output the results.
	 */
	CUTE_FORMAT_XML,

	/**
	 * \brief Display the results in a format designed for a console window.
	 *
	 * \note This format uses ANSI color codes, which are not supported by all
	 *       terminal emulators.
	 */
	CUTE_FORMAT_CONSOLE,
} CUTE_LogFormat;


/**
 * \brief Performs the actual logging of the results.
 *
 * \param[in] number  The number of cases to output
 * \param[in] results The results of the test cases run
 * \param[in] logfile The file where to log
 * \param[in] format  The format to log into
 */
void CUTE_logResults(unsigned int number,
                     const CUTE_RunResults *results[number], FILE *logfile,
					 CUTE_LogFormat format) CUTE_NOTNULL(2, 3);

/**
 * \brief Prints the results to the console, on standard output, as simple text.
 *
 * \param[in] number  The number of cases to output
 * \param[in] results The results of the test cases run
 *
 * \sa CUTE_logResults
 */
CUTE_INLINE CUTE_NOTNULL(2)
void CUTE_printResults(unsigned int number,
                       const CUTE_RunResults *results[number]) {
	CUTE_logResults(number, results, stdout, CUTE_FORMAT_CONSOLE);
}
