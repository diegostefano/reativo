#ifndef __FUZZY_SET_H__
#define	__FUZZY_SET_H__

#include "defines.h"

typedef struct {
	char name[MAXSTR];
	enum MF_TYPE type;
	float params[4];
} fuzzy_set;

void create_fuzzy_set(
    fuzzy_set *fs,
    const char *name,
    enum MF_TYPE type,
    double p1, double p2, double p3, double p4);
void create_fuzzy_sets(volatile fuzzy_set fs[], unsigned char n_sets, ...);
//void print_fuzzy_sets(fuzzy_set *s, int n);

#endif // !__FUZZY_SET_H__
