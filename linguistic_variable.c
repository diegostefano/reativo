#include <stdarg.h>
#include <string.h>

#include "linguistic_variable.h"

void create_linguistic_variable(linguistic_variable *lvar, const char name[MAXSTR], float min_range, float max_range, unsigned char n, fuzzy_set *mfs) {
	//strcpy_s(lvar->name, strlen(name) + 1, name);
    strcpy(lvar->name, name);

	lvar->range[0] = min_range;
	lvar->range[1] = max_range;

	lvar->n = n;
	lvar->fuzzy_sets = mfs;
}

void create_linguistic_variables(linguistic_variable *lvar, unsigned char n_vals, ...) {
	va_list vl;

	va_start(vl, n_vals);

	for (int v = 0; v < n_vals; v++)
		create_linguistic_variable(
			&lvar[v],
			va_arg(vl, char *),
			va_arg(vl, double),
			va_arg(vl, double),
			va_arg(vl, unsigned char),
			va_arg(vl, fuzzy_set *));

	va_end(vl);
}