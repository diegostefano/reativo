#ifndef __LINGUISTIC_VARIABLE_H__
#define	__LINGUISTIC_VARIABLE_H__

#include "defines.h"
#include "fuzzy_set.h"

typedef struct {
	char name[MAXSTR];
	float range[2];
	fuzzy_set *fuzzy_sets;
	unsigned char n;
} linguistic_variable;

void create_linguistic_variable(
    linguistic_variable *lvar,
    const char name[MAXSTR],
    float min_range,
    float max_range,
    unsigned char n,
    fuzzy_set *mfs);
void create_linguistic_variables(linguistic_variable *lvar, unsigned char n_vals, ...);

#endif // !__LINGUISTIC_VARIABLE_H__

