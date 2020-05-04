/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "defines.h"
#include "fis.h"
#include "fuzzy_set.h"
#include "linguistic_variable.h"
#include "membership_functions.h"

#ifndef GAIN_SCHEDULING_KB_H
    #define GAIN_SCHEDULING_KB_H
    
    #define MAX_VEL             31.4
    #define MFDELTA             8
    #define ERRMF(i)            -MAX_VEL+(2*MAX_VEL)*i/MFDELTA
    #define DERRMF(i)           2*ERRMF(i)
    
    // Input Membership Functions
    // --------------------------
    // "mf_error" and "mf_derror": Negative big, medium and small (NB, NM, NS),
    // aproximately zero (ZO) and Negative big, medium and small (NB, NM, NS);
    // "mf_alpha": small (S or 2), medium small (MS or 3), medium (M or 4) and
    // big (B or 5).
	fuzzy_set mf_error[7],
              mf_derror[7];
    
    // Output Membership Functions
    fuzzy_set mf_Kp[2],
              mf_Kd[2],
              mf_alpha[4];
            
    // Input Linguistic Variables
	linguistic_variable lv_error, lv_derror;
            
    // Output Linguistic Variables
    linguistic_variable lv_Kp, lv_Kd, lv_alpha;
            
	rule rules[49];
	char rules_str[49][5][MAXSTR] = {
		{ "NB", "NB", "B", "S", "2" },
	    { "NB", "NM", "B", "S", "2" },
		{ "NB", "NS", "B", "S", "2" },
		{ "NB", "ZO", "B", "S", "2" },
		{ "NB", "PS", "B", "S", "2" },
		{ "NB", "PM", "B", "S", "2" },
		{ "NB", "PB", "B", "S", "2" },

		
		{ "NM", "NB", "S", "B", "3" },
	    { "NM", "NM", "B", "B", "3" },
		{ "NM", "NS", "B", "S", "2" },
		{ "NM", "ZO", "B", "S", "2" },
		{ "NM", "PS", "B", "S", "2" },
		{ "NM", "PM", "B", "B", "3" },
		{ "NM", "PB", "S", "B", "3" },

		
		{ "NS", "NB", "S", "B", "4" },
	    { "NS", "NM", "S", "B", "3" },
		{ "NS", "NS", "B", "B", "3" },
		{ "NS", "ZO", "B", "S", "2" },
		{ "NS", "PS", "B", "B", "3" },
		{ "NS", "PM", "S", "B", "3" },
		{ "NS", "PB", "S", "B", "4" },

		
		{ "ZO", "NB", "S", "B", "5" },
	    { "ZO", "NM", "S", "B", "4" },
		{ "ZO", "NS", "S", "B", "3" },
		{ "ZO", "ZO", "B", "B", "3" },
		{ "ZO", "PS", "S", "B", "3" },
		{ "ZO", "PM", "S", "B", "4" },
		{ "ZO", "PB", "S", "B", "5" },

		
		{ "PS", "NB", "S", "B", "4" },
	    { "PS", "NM", "S", "B", "3" },
		{ "PS", "NS", "B", "B", "3" },
		{ "PS", "ZO", "B", "S", "2" },
		{ "PS", "PS", "B", "B", "3" },
		{ "PS", "PM", "S", "B", "3" },
		{ "PS", "PB", "S", "B", "4" },
        
        
		{ "PM", "NB", "S", "B", "3" },
	    { "PM", "NM", "B", "B", "3" },
		{ "PM", "NS", "B", "S", "2" },
		{ "PM", "ZO", "B", "S", "2" },
		{ "PM", "PS", "B", "S", "2" },
		{ "PM", "PM", "B", "B", "3" },
		{ "PM", "PB", "S", "B", "3" },
        
        
		{ "PB", "NB", "B", "S", "2" },
	    { "PB", "NM", "B", "S", "2" },
		{ "PB", "NS", "B", "S", "2" },
		{ "PB", "ZO", "B", "S", "2" },
		{ "PB", "PS", "B", "S", "2" },
		{ "PB", "PM", "B", "S", "2" },
		{ "PB", "PB", "B", "S", "2" },
	};
    
    void init_gs_kb() {
        create_fuzzy_set(&mf_error[0], "NB", TRAPEZOIDAL,  ERRMF(-1), ERRMF(0), ERRMF(1), ERRMF(2));
    	create_fuzzy_set(&mf_error[1], "NM", TRIANGULAR,    ERRMF(1), ERRMF(2), ERRMF(3),     0.0f);
    	create_fuzzy_set(&mf_error[2], "NS", TRIANGULAR,    ERRMF(2), ERRMF(3), ERRMF(4),     0.0f);
    	create_fuzzy_set(&mf_error[3], "ZO", TRIANGULAR,    ERRMF(3), ERRMF(4), ERRMF(5),     0.0f);
    	create_fuzzy_set(&mf_error[4], "PS", TRIANGULAR,    ERRMF(4), ERRMF(5), ERRMF(6),     0.0f);
    	create_fuzzy_set(&mf_error[5], "PM", TRIANGULAR,    ERRMF(5), ERRMF(6), ERRMF(7),     0.0f);
        create_fuzzy_set(&mf_error[6], "PB", TRAPEZOIDAL,   ERRMF(6), ERRMF(7), ERRMF(8), ERRMF(9));
        
        create_fuzzy_set(&mf_derror[0], "NB", TRAPEZOIDAL,  DERRMF(-1), DERRMF(0), DERRMF(1), DERRMF(2));
    	create_fuzzy_set(&mf_derror[1], "NM", TRIANGULAR,    DERRMF(1), DERRMF(2), DERRMF(3),     0.0f);
    	create_fuzzy_set(&mf_derror[2], "NS", TRIANGULAR,    DERRMF(2), DERRMF(3), DERRMF(4),     0.0f);
    	create_fuzzy_set(&mf_derror[3], "ZO", TRIANGULAR,    DERRMF(3), DERRMF(4), DERRMF(5),     0.0f);
    	create_fuzzy_set(&mf_derror[4], "PS", TRIANGULAR,    DERRMF(4), DERRMF(5), DERRMF(6),     0.0f);
    	create_fuzzy_set(&mf_derror[5], "PM", TRIANGULAR,    DERRMF(5), DERRMF(6), DERRMF(7),     0.0f);
        create_fuzzy_set(&mf_derror[6], "PB", TRAPEZOIDAL,   DERRMF(6), DERRMF(7), DERRMF(8), DERRMF(9));

    	create_fuzzy_set(&mf_Kd[0], "S", TRIANGULAR, -0.0f, 0.0f, 1.0f, 0);
        create_fuzzy_set(&mf_Kd[1], "B", TRIANGULAR, 0.0f, 1.0f, 1.0f, 0);

    	create_fuzzy_set(&mf_Kp[0], "S", TRIANGULAR, -0.0f, 0.0f, 1.0f, 0);
        create_fuzzy_set(&mf_Kp[1], "B", TRIANGULAR, 0.0f, 1.0f, 1.0f, 0);
        
        create_fuzzy_set(&mf_alpha[0], "2", TRIANGULAR, 1.99f, 2.0f, 2.01f, 0.0f);
        create_fuzzy_set(&mf_alpha[1], "3", TRIANGULAR, 2.99f, 3.0f, 3.01f, 0.0f);
        create_fuzzy_set(&mf_alpha[2], "4", TRIANGULAR, 3.99f, 4.0f, 4.01f, 0.0f);
        create_fuzzy_set(&mf_alpha[3], "5", TRIANGULAR, 4.99f, 5.0f, 5.01f, 0.0f);

    	create_linguistic_variable(&lv_error, "error", -MAX_VEL, MAX_VEL, 7, mf_error);
    	create_linguistic_variable(&lv_derror, "derror", -2.0f*MAX_VEL, 2.0f*MAX_VEL, 7, mf_derror);
    	create_linguistic_variable(&lv_Kp, "Kp", 0.0f, 1.0f, 2, mf_Kp);
    	create_linguistic_variable(&lv_Kd, "Kd", 0.0f, 1.0f, 2, mf_Kd);
    	create_linguistic_variable(&lv_alpha, "alpha", 1.9f, 5.1f, 4, mf_alpha);
        
    	for (int r = 0; r < 49; r++) {
    		rules[r].n_in = 2;
    		rules[r].n_out = 3;

    		create_sentence(
                &rules[r].lhs, 2,
                &lv_error, rules_str[r][0],
                &lv_derror, rules_str[r][1]
            );
            
    		create_sentence(
                &rules[r].rhs, 3,
                &lv_Kp, rules_str[r][2],
                &lv_Kd, rules_str[r][3],
                &lv_alpha, rules_str[r][4]
            );
    	}
    }
#endif
/* [] END OF FILE */
