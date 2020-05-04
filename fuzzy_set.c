#include <stdarg.h>
#include <string.h>

#include "fuzzy_set.h"

void _strcpy(char *dst, const char *src, int len) {
    for (int i = 0; i < len - 1; i++) dst[i] = src[i];
}

void create_fuzzy_set(
    fuzzy_set *fs,
    const char *name,
    enum MF_TYPE type,
    double p1, double p2, double p3, double p4)
{
    strcpy(fs->name, name);
    fs->type = type;
    fs->params[0] = p1;
    fs->params[1] = p2;
    fs->params[2] = p3;
    fs->params[3] = p4;
}

void create_fuzzy_sets(volatile fuzzy_set fs[], unsigned char n_sets, ...) {
	va_list vl;
	va_start(vl, n_sets);

	for (int s = 0; s < n_sets; s++) {
		//volatile char *name = va_arg(vl, char *);
        //int len = strlen(name);
		//strcpy_s(fs[s].name, strlen(name) + 1, name);
        //strcpy(fs[s].name, name);
        va_arg(vl, char *);
        
        fs[s].type = va_arg(vl, enum MF_TYPE);
		fs[s].params[0] = va_arg(vl, double);
		fs[s].params[1] = va_arg(vl, double);
        
        for (int i = 0; i < 3; i++)
            fs[s].name[i] = 'o';

		if (fs[s].type == TRIANGULAR) {
			fs[s].params[2] = va_arg(vl, double);
		}
		else if (fs[s].type == TRAPEZOIDAL) {
			fs[s].params[2] = va_arg(vl, double);
			fs[s].params[3] = va_arg(vl, double);
		}
	}

	va_end(vl);
}

/*void print_fuzzy_sets(fuzzy_set *s, int n) {
	for (int i = 0; i < n; i++) {
		printf("+++++++++++ SET %i +++++++++++\n", i);
		printf("NAME: %s\nTYPE: %s\n", s[i].name, (s[i].type == TRIANGULAR ? "trimf" : (s[i].type == TRAPEZOIDAL ? "trapmf" : "gaussmf")));

		if (s[i].type == TRIANGULAR)
			printf("a: %.2f; b: %.2f; c: %.2f;\n", s[i].params[0], s[i].params[1], s[i].params[2]);
		else
			printf("a: %.2f; b: %.2f; c: %.2f; d: %.2f\n", s[i].params[0], s[i].params[1], s[i].params[2], s[i].params[3]);

		printf("+++++++++++++++++++++++++++++\n");
	}
}*/
