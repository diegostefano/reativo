#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include "fis.h"
#include "membership_functions.h"

#include "UART.h"

void create_sentence(sentence *p, unsigned char n_vars, ...) {
	va_list vl;

	p->n = n_vars;

	linguistic_variable *lvar;
	char *value;

	va_start(vl, n_vars);

	for (int v = 0; v < n_vars; v++) {
		lvar = va_arg(vl, linguistic_variable *);

		create_linguistic_variable(
			&p->ling_vars[v],
			lvar->name,
			lvar->range[0],
			lvar->range[1],
			lvar->n,
			lvar->fuzzy_sets);

		value = va_arg(vl, char *);

		for (int idx = 0; idx < lvar->n; idx++) {
			if (strcmp(value, lvar->fuzzy_sets[idx].name) == 0) {
				p->idxs[v] = idx;
				break;
			}
		}
	}

	va_end(vl);
}

void inference(rule *rules, unsigned char n, enum T_NORM and, enum T_NORM implication, float *x, float *y) {
    float output_area_sum[MAXOUTVARS] = { 0.0f };
	for (int r = 0; r < n; r++) {
		float conjunction = (and == MIN ?
            INT_MAX : (and == PROD? 1.0f : -INT_MAX));

		for (int in = 0; in < rules[r].n_in; in++) {
            unsigned char idx = rules[r].lhs.idxs[in];
			fuzzy_set *f = &rules[r].lhs.ling_vars[in].fuzzy_sets[idx];
			float mu;

			switch (f->type) {
			case TRIANGULAR:
				mu = trimf(x[in], f->params[0], f->params[1], f->params[2]);
				break;

			case TRAPEZOIDAL:
				mu = trapmf(x[in], f->params[0], f->params[1], f->params[2], f->params[3]);
				break;

			default:
				mu = trimf(x[in], f->params[0], f->params[1], f->params[2]);
			}

			conjunction = (and == MIN ?
                min(conjunction, mu) : (and == PROD ?
                    conjunction * mu : max(0, conjunction + mu - 1)));
		}

		if (conjunction > 0.0001f) {
			for (int out = 0; out < rules[r].n_out; out++) {
				if (r == 0) {
					y[out] = 0.0f;
					output_area_sum[out] = 0.0f;
				}

				float current_area, current_centroid;
                unsigned char idx = rules[r].rhs.idxs[out];
				fuzzy_set *f = &rules[r].rhs.ling_vars[out].fuzzy_sets[idx];

				switch (f->type) {
				case TRIANGULAR:
					current_area = trimf_area(conjunction, f->params[0], f->params[1], f->params[2], implication);
					current_centroid = trimf_cogx(conjunction, f->params[0], f->params[1], f->params[2], implication);
					break;

				case TRAPEZOIDAL:
					current_area = trapmf_area(conjunction, f->params[0], f->params[1], f->params[2], f->params[3], implication);
					current_centroid = trapmf_cogx(conjunction, f->params[0], f->params[1], f->params[2], f->params[3], implication);
					break;

				default:
					current_area = trimf_area(conjunction, f->params[0], f->params[1], f->params[2], implication);
					current_centroid = trimf_cogx(conjunction, f->params[0], f->params[1], f->params[2], implication);
				}

				output_area_sum[out] += conjunction;
				y[out] += (current_centroid) * (conjunction);
			}
		}
		else if (r == 0) {
			for (int out = 0; out < rules[r].n_out; out++) {
				y[out] = 0.0f;
				output_area_sum[out] = 0.0f;
			}
		}
	}
    
    for (int out = 0; out < MAXOUTVARS; out++)
	    y[out] = (output_area_sum[out] > 0.0f ? y[out] / output_area_sum[out] : 0.0f);
}

//void create_sentence(sentence *pr, unsigned char n_vars, ...) {
//    sentence *p = pr;
//	va_list vl;
//    char temp[50];
//	p->n = n_vars;
//	//p->idxs = (unsigned char *)malloc(n_vars * sizeof(unsigned char));
//	//p->ling_vars = (linguistic_variable *)malloc(n_vars * sizeof(linguistic_variable));
//
//	linguistic_variable *lvar;
//	char *value;
//
//	va_start(vl, n_vars);
//
//	for (int v = 0; v < n_vars; v++) {
//		lvar = va_arg(vl, linguistic_variable *);
//
//		create_linguistic_variable(
//			&p->ling_vars[v],
//			lvar->name,
//			lvar->range[0],
//			lvar->range[1],
//			lvar->n,
//			lvar->fuzzy_sets);
//
//		value = va_arg(vl, char *);
//
//		for (unsigned char idx = 0; idx < lvar->n; idx++) {
//			if (strcmp(value, lvar->fuzzy_sets[idx].name) == 0) {
//				p->idxs[v] = idx;
//                
//                /*sprintf(temp, "===>>> p->idxs[%d] = %d (%d)\n\r",
//                    v, p->idxs[v], idx);
//                UART_PutString(temp);*/
//                
//				break;
//			}
//		}
//	}
//
//	va_end(vl);
//}
//
///*void print_sentence(sentence *p) {
//	printf("***************************\n");
//	printf("IF {");
//	for (int i = 0; i < p->n; i++) {
//		printf("(%s is %s)", p->ling_vars[i].name, p->ling_vars[i].fuzzy_sets[p->idxs[i]].name);
//		if (i < p->n - 1) printf(" AND ");
//	}
//	printf("} THEN {}\n");
//	printf("***************************\n");
//}*/
//
//void cleanup(rule *r, unsigned char n_rules) {
//	for (int i = 0; i < n_rules; i++) {
//		//free(r[i].lhs->idxs);
//		//free(r[i].lhs->ling_vars);
//
//		//free(r[i].rhs->idxs);
//		//free(r[i].rhs->ling_vars);
//
//		//free(r[i].lhs);
//		//free(r[i].rhs);
//	}
//}
//
//void inference(rule *_rules, unsigned char n, float *output_area_sum, enum T_NORM and, enum T_NORM implication, float *x, float *y) {
//    rule *rules = _rules;
//    /*char temp[50];
//    for (int r = 0; r < n; r++) {
//        sprintf(temp, "rule[%d}: n_in=%d\n\r", r, rules[r].n_in);
//        UART_PutString(temp);
//      
//    }*/
//    for (int r = 0; r < n; r++) {
//		//printf("-- Processing rule %d...\n", r);
//		float conjunction = (and == MIN ? INT_MAX : (and == PROD? 1.0f : -INT_MAX));
//
//		for (int in = 0; in < rules[r].n_in; in++) {
//			//sprintf(temp, "In: %d; Idx: %d\r\n", in, rules[r].lhs.idxs[in]);
//            //UART_PutString(temp);
//            
//			fuzzy_set *f = &rules[r].lhs.ling_vars[in].fuzzy_sets[rules[r].lhs.idxs[in]];
//			float mu;
//
//			switch (f->type) {
//			case TRIANGULAR:
//				mu = trimf(x[in], f->params[0], f->params[1], f->params[2]);
//				break;
//
//			case TRAPEZOIDAL:
//				mu = trapmf(x[in], f->params[0], f->params[1], f->params[2], f->params[3]);
//				break;
//
//			default:
//				mu = trimf(x[in], f->params[0], f->params[1], f->params[2]);
//			}
//
//			conjunction = (and == MIN ? min(conjunction, mu) : (and == PROD ? conjunction * mu : max(0, conjunction + mu - 1)));
//		}
//
//		if (conjunction > 0.0001f) {
//			for (int out = 0; out < rules[r].n_out; out++) {
//				//printf("---- Processing output %d...\n", out);
//				if (r == 0) {
//					y[out] = 0.0f;
//					output_area_sum[out] = 0.0f;
//				}
//
//				float current_area, current_centroid;
//				fuzzy_set *f = &rules[r].rhs.ling_vars[out].fuzzy_sets[rules[r].rhs.idxs[out]];
//
//				switch (f->type) {
//				case TRIANGULAR:
//					current_area = trimf_area(conjunction, f->params[0], f->params[1], f->params[2], implication);
//					current_centroid = trimf_cogx(conjunction, f->params[0], f->params[1], f->params[2], implication);
//					break;
//
//				case TRAPEZOIDAL:
//					current_area = trapmf_area(conjunction, f->params[0], f->params[1], f->params[2], f->params[3], implication);
//					current_centroid = trapmf_cogx(conjunction, f->params[0], f->params[1], f->params[2], f->params[3], implication);
//					break;
//
//				default:
//					current_area = trimf_area(conjunction, f->params[0], f->params[1], f->params[2], implication);
//					current_centroid = trimf_cogx(conjunction, f->params[0], f->params[1], f->params[2], implication);
//				}
//
//				output_area_sum[out] += conjunction;
//				y[out] += (current_centroid) * (conjunction);
//			}
//		}
//		else if (r == 0) {
//			for (int out = 0; out < rules[r].n_out; out++) {
//				y[out] = 0.0f;
//				output_area_sum[out] = 0.0f;
//			}
//		}
//	}
//    
//	y[0] = (output_area_sum[0] > 0.0f ? y[0] / output_area_sum[0] : 0.0f);
//}
//