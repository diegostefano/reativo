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

#include "aux_functions.h"

float powf(float b, float e) {
    if (e == 1.0f)
        return b;
    else {
        return b * powf(b, e - 1.0f);
    }
}

void float2string(float number, char string[], uint8 precision) {
    int characteristic = (int)number;
    float mantissa =
        (number > 0 ? number - (float)characteristic : -number + (float)characteristic);
    int uint_mantissa =
        (int)(powf(10.0f, (float)precision) * mantissa);
       
    sprintf(string, "%d.%d\0", characteristic, uint_mantissa);
}

void nova(float n, float *vec, uint8 tam) {
    for (int i = 0; i < tam - 1; i++)
        vec[i + 1] = vec[i];
        
    vec[0] = n;
}

float media(float *vec, uint8 tam) {
    float soma = 0.0;
    
    for (int i = 0; i < tam; i++)
        soma += vec[i];
        
    return (soma / tam);
}

/* [] END OF FILE */
