/* 
 * membership_functions.h
 * ------------------------------------------------
 * DESCRIPTION: defines functions that implements fuzzy membership functions and
 *              their geometric properties given an input.
 * ------------------------------------------------
 * AUTHOR: Diego Stéfano (diego.stefano <at> gmail <dot> com)
 */
    
#ifndef __MEMBERSHIP_FUNCTIONS_H__
#define	__MEMBERSHIP_FUNCTIONS_H__

#include "defines.h"

/* 
 trapmf - Calculates the membership of an input "x" for a trapezoidal fuzzy set on
          the left-hand side (LHS).
 ------------------------------------------------
 Arguments:
    float x - input data;
    float a - left-most position of bigger base;
    float b - left-most position of smaller base;
    float c - right-most position of smaller base;
    float d - right-most position of smaller base;
    
 Return:
    float - membership of input data to the given set.
 */
float trapmf(float x, float a, float b, float c, float d);

/* 
 trapmf_area - Calculates the area of a right-hand side (RHS) trapezoidal fuzzy set
               given the left-hand side conjunction result "y" and an implication method.
 ------------------------------------------------
 Arguments:
    float y - result of a LHS conjuntion;
    float a - left-most position of bigger base;
    float b - left-most position of smaller base;
    float c - right-most position of smaller base;
    float d - right-most position of smaller base;
    enum T_NORM implication - the way this area will be weighted by "y":
        MIN - cuts upper part of this set where membership equals "y", i. e.,
              it becomes trapmf(a, y*(b-a)+a, -y*(d-c)+d, d);
        PROD - multiplies current trapezoid by "y", changing only its height.
    
 Return:
    float - membership of input data to the given set.
 */
float trapmf_area(float y, float a, float b, float c, float d, enum T_NORM implication);
float trapmf_cogx(float y, float a, float b, float c, float d, enum T_NORM implication);

float trimf(float x, float a, float b, float c);
float trimf_area(float y, float a, float b, float c, enum T_NORM implication);
float trimf_cogx(float y, float a, float b, float c, enum T_NORM implication);

#endif // !__MEMBERSHIP_FUNCTIONS_H__

