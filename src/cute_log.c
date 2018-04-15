#include "cute_test.h"

#include <stdlib.h> /* for NULL */
#include <time.h> /* for time_t, localtime, strftime */



typedef void (LogFunc)(unsigned int, const CUTE_RunResults*[], FILE*);
static LogFunc _log_text, _log_xml, _log_console;
static LogFunc *_log[] = {
	[CUTE_FORMAT_TEXT] = _log_text,
	[CUTE_FORMAT_XML] = _log_xml,
	[CUTE_FORMAT_CONSOLE] = _log_console,
};

static const char *_statutes[] = {
	[CUTE_STATUS_SUCCESS] = ".Success",
	[CUTE_STATUS_FAILURE] = "!Failure",
	[CUTE_STATUS_ERROR] = "xError",
	[CUTE_STATUS_IGNORED] = "-Ignored",
	[CUTE_STATUS_SKIPPED] = ",Skipped",
	[CUTE_STATUS_CANCELED] = "/Canceled"
};


void CUTE_logResults(const unsigned int n, const CUTE_RunResults *r[n],
                     FILE *const f, const CUTE_LogFormat fmt) {
	_log[fmt](n, r, f);
}


static CUTE_INLINE void _gettime(const unsigned int n, char s[n],
                                 const char *const fmt) {
	time_t t;
	time(&t);
	strftime(s, n, fmt, localtime(&t));
}

void _log_text(const unsigned int n, const CUTE_RunResults *r[n],
               FILE *const f) {
	char t[20];
	_gettime(20, t, "%F %T");
	fprintf(f, "Logging tests execution at %s\n", t);
	for(unsigned int i = 0; i < n; ++i) {
		fprintf(f, "Test case #%u, \"%s\" %u/%u\n", i, r[i]->title,
		        r[i]->successes, r[i]->total);
		for(unsigned int j = 0; j < r[i]->total; ++j) {
			fprintf(f, "Test #%u.%u: %s, %s (%.3f s)\n", i, j,
			        r[i]->results[j].name, _statutes[r[i]->results[j].status]+1,
			        r[i]->results[j].time);
			/* TODO print extra */
		}
	}
}

void _log_xml(const unsigned int n, const CUTE_RunResults *r[n],
              FILE *const f) {
	char t[21];
	_gettime(21, t, "%FT%TZ");
	fputs("<?xml encoding=\"UTF-8\" version=\"1.0\" standalone=\"no\"?>\n", f);
	fputs("<!DOCTYPE run SYSTEM \"cute.dtd\">\n", f);
	fprintf(f, "<run logdate=\"%s\">\n", t);
	for(unsigned int i = 0; i < n; ++i) {
		fprintf(f, "\t<case title=\"%s\" total=\"%u\" successes=\"%u\">\n",
		        r[i]->title, r[i]->total, r[i]->successes);
		for(unsigned int j = 0; j < r[i]->total; ++j) {
			fputs("\t\t<test>\n", f);
			fprintf(f, "\t\t\t<name>%s</name>\n", r[i]->results[j].name);
			fprintf(f, "\t\t\t<status>%s</status>\n",
			        _statutes[r[i]->results[j].status] + 1);
			fprintf(f, "\t\t\t<time>%.3f</time>\n", r[i]->results[j].time);
			/* TODO print extra */
			fputs("\t\t</test>\n", f);
		}
		fputs("\t</case>\n", f);
	}
	fputs("</run>\n", f);
}

static void _printtest(FILE *const f, const char *const c,
                       const CUTE_TestResult *const tr) {
	static const char testclrs[][3] = {
		[CUTE_STATUS_SUCCESS] = "92", /* bright blue */
		[CUTE_STATUS_FAILURE] = "91", /* bright red */
		[CUTE_STATUS_ERROR] = "31",   /* red */
		[CUTE_STATUS_IGNORED] = "90", /* bright black (dark grey) */
		[CUTE_STATUS_SKIPPED] = "36", /* cyan */
		[CUTE_STATUS_CANCELED] = "34" /* blue */
	};
	const CUTE_TestStatus s = tr->status;
	fprintf(f, "%s\u2500 \x1b[1;7;%sm %c \x1b[0m %s (%s, %.3f s)\n", c,
	        testclrs[s], _statutes[s][0], tr->name, _statutes[s] + 1, tr->time);
}
void _log_console(const unsigned int n, const CUTE_RunResults *r[n],
                  FILE *const f) {
	for(unsigned int i = 0; i < n; ++i) {
		fprintf(f, "%s\n", r[i]->title);
		unsigned int j;
		for(j = 0; j < r[i]->total - 1; ++j) {
			_printtest(f, "\u251c", &(r[i]->results[j]));
		}
		_printtest(f, "\u2514", &(r[i]->results[j]));
	}
}
