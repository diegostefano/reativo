#ifndef __FIS_H__
#define	__FIS_H__

#include "defines.h"
#include "fuzzy_set.h"
#include "linguistic_variable.h"

/*
    STRUCTURE: "sentence"
    ---------------------
    
    Description: represents a conjunction (this library doesn't support
                 disjunction yet) of equality comparisons between linguistic
                 variables and linguistic values (fuzzy sets).
    
    Members:
    "ling_vars": array of "linguistic_variable" objects that will compose the
                 left-hand side of the comparisons.
    "idx"      : array of "unsigned char" whose i-th element is the index of
                 the fuzzy set inside the i-th linguistic variable in the array
                 "ling_vars" that the i-th linguistic variable will be compared
                 to.
    "n"        : the length of the above arrays.
    
 */
typedef struct {
	unsigned char idxs[MAXINVARS];
	linguistic_variable ling_vars[MAXINVARS];
	unsigned char n;
} sentence;

typedef struct {
	sentence lhs, rhs;
	unsigned char n_in, n_out;
} rule;

void create_sentence(sentence *p, unsigned char n_vars, ...);

//void print_sentence(sentence *p);

void cleanup(rule *r, unsigned char n_rules);

void inference(
    rule *rules,
    unsigned char n,
    enum T_NORM and,
    enum T_NORM implication,
    float x[],
    float y[]
);

#endif // !__FIS_H__

