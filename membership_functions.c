#include <stdlib.h>

#include "membership_functions.h"
#include "defines.h"

float trapmf(float x, float a, float b, float c, float d) {
    float mu = max(min(min((x - a) / (b - a), 1), (d - x) / (d - c)), 0);
    /*float mu;
    if (x > a && x < b)
        mu = (x - a) / (b - a);
    else if (x >= b && x <= c)
        mu = 1.0f;
    else if (x > c && x < d)
        mu = (d - x) / (d - c);
    else
        mu = 0.0f;*/
        
	return mu;
}

float trapmf_area(float y, float a, float b, float c, float d, enum T_NORM implication) {
	if (implication == PROD)
		return ((d - a) + (c - b)) * y / 2.0f;
	else { // MIN
		float x_min = y * (b - a) + a,
			x_max = -y * (d - c) + d;

		return ((d - a) + (x_max - x_min)) * y / 2.0f;
	}
}

float trapmf_cogx(float y, float a, float b, float c, float d, enum T_NORM implication) {
	float _a, _b, _c;

	if (implication == PROD) {
		_a = c - b,
			_b = d - a,
			_c = b - a;
	}
	else {
		float x_min = y * (b - a) + a,
			x_max = -y * (d - c) + d;

		_a = x_max - x_min,
			_b = d - a,
			_c = x_min - a;
	}

	return a + (2 * _a * _b + _a * _a + _c * _b + _b * _b) / (3 * (_a + _b));
}

float trimf(float x, float a, float b, float c) {
	return max(min((x - a) / (b - a), (c - x) / (c - b)), 0);
}

float trimf_area(float y, float a, float b, float c, enum T_NORM implication) {
	if (implication == PROD)
		return (c - a) * y / 2.0f;
	else { // MIN
		float x_min = y * (b - a) + a,
			x_max = -y * (c - b) + c;

		return ((c - a) + (x_max - x_min)) * y / 2.0f;
	}
}

float trimf_cogx(float y, float a, float b, float c, enum T_NORM implication) {
	if (implication == PROD)
		return a + ((c - a) + (b - a)) / 3.0f;
	else { // MIN
		float x_min = y * (b - a) + a,
			x_max = -y * (c - b) + c;

		return trapmf_cogx(y, a, x_min, x_max, c, implication);
	}
}
