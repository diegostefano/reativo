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

#include "project.h"

#ifndef __AUX_FUNCTIONS_H__
#define __AUX_FUNCTIONS_H__

float powf(float b, float e);
void float2string(float number, char string[], uint8 precision);
void nova(float n, float *vec, uint8 tam);
float media(float *vec, uint8 tam);

union Data {
    float word;
    char bytes[4];
};

#endif

/* [] END OF FILE */
