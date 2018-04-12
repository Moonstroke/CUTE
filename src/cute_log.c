#include "cute_test.h"

#include <stdlib.h> /* for NULL */
#include <time.h> /* for time_t, localtime, strftime */



static CUTE_LogFormat _format = CUTE_FORMAT_TEXT;
static FILE *_file = NULL;

static void _log_text(unsigned int, const CUTE_RunResults *const[]);
static void _log_xml(unsigned int, const CUTE_RunResults *const[]);
static void (*_log[])(unsigned int, const CUTE_RunResults *const[]) = {
	[CUTE_FORMAT_TEXT] = _log_text,
	[CUTE_FORMAT_XML] = _log_xml,
};

static const char *_statutes[] = {
	[CUTE_STATUS_SUCCESS] = "Success",
	[CUTE_STATUS_FAILURE] = "Failure",
	[CUTE_STATUS_ERROR] = "Error",
	[CUTE_STATUS_IGNORED] = "Ignored",
	[CUTE_STATUS_SKIPPED] = "Skipped",
	[CUTE_STATUS_CANCELED] = "Canceled"
};


void CUTE_setLogFormat(const CUTE_LogFormat f) {
	_format = f;
}

void CUTE_setLogFile(FILE *const f) {
	_file = f;
}

void CUTE_logResults(const unsigned int n, const CUTE_RunResults *r[n]) {
	if(_file == NULL) {
		_file = stderr;
	}
	_log[_format](n, r);
}


static CUTE_INLINE void _printtime(const unsigned int n, char s[n],
	                               const char *const fmt) {
	time_t t;
	time(&t);
	strftime(s, n, fmt, localtime(&t));
}

void _log_text(const unsigned int n, const CUTE_RunResults *const r[n]) {
	char t[20];
	_printtime(20, t, "%F %T");
	fprintf(_file, "Logging tests execution at %s\n", t);
	for(unsigned int i = 0; i < n; ++i) {
		fprintf(_file, "Test case #%u, \"%s\" %u/%u\n", i, r[i]->title,
		        r[i]->successes, r[i]->total);
		for(unsigned int j = 0; j < r[i]->total; ++j) {
			fprintf(_file, "Test #%u.%u: %s, %s\n", i, j, r[i]->results[j].name,
			        _statutes[r[i]->results[j].status]);
			/* TODO print extra */
		}
	}
}

void _log_xml(const unsigned int n, const CUTE_RunResults *const r[n]) {
	char t[21];
	_printtime(21, t, "%FT%TZ");
	fputs("<?xml encoding=\"UTF-8\" version=\"1.0\" standalone=\"no\"?>\n",
	      _file);
	fputs("<!DOCTYPE run SYSTEM \"cute.dtd\">\n", _file);
	fprintf(_file, "<run logdate=\"%s\">\n", t);
	for(unsigned int i = 0; i < n; ++i) {
		fprintf(_file, "\t<case title=\"%s\" total=\"%u\" successes=\"%u\">\n",
		        r[i]->title, r[i]->total, r[i]->successes);
		for(unsigned int j = 0; j < r[i]->total; ++j) {
			fputs("\t\t<test>\n", _file);
			fprintf(_file, "\t\t\t<name>%s</name>\n", r[i]->results[j].name);
			fprintf(_file, "\t\t\t<status>%s</status>\n",
			        _statutes[r[i]->results[j].status]);
			/* TODO print extra */
			fputs("\t\t</test>\n", _file);
		}
		fputs("\t</case>\n", _file);
	}
	fputs("</run>\n", _file);
}
