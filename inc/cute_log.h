#ifndef CUTE_TEST_H
#error "This file must not be included directly"
#endif

#include <stdio.h> /* for FILE, fprintf, fputs */

#include "cute_test.h"



typedef enum {
	CUTE_FORMAT_TEXT,
	CUTE_FORMAT_XML,
} CUTE_LogFormat;


void CUTE_setLogFormat(CUTE_LogFormat format);

void CUTE_setLogFile(FILE *file) CUTE_NOTNULL(1);


void CUTE_logResults(unsigned int number,
                     const CUTE_RunResults *results[number]);
