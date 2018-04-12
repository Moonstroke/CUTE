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

#include <stdio.h> /* for FILE, fprintf, fputs */

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
} CUTE_LogFormat;


/**
 * \brief Specifies the log format to output the resutls with.
 *
 * \note The default value is \c CUTE_FORMAT_TEXT.
 *
 * \param[in] format The output format to use.
 */
void CUTE_setLogFormat(CUTE_LogFormat format);

/**
 * \brief Specifies the file where to log the results.
 *
 * \note If none is ever specified, output is done to \c stderr.
 *
 * \param[in] file The file handle to use
 */
void CUTE_setLogFile(FILE *file) CUTE_NOTNULL(1);


/**
 * \brief Performs the actual logging of the results.
 *
 * \param[in] number  The number of cases to output
 * \param[in] results The resrults of the test cases run
 */
void CUTE_logResults(unsigned int number,
                     const CUTE_RunResults *results[number]);
