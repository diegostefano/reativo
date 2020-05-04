#ifndef __DEFINES_H__
#define	__DEFINES_H__

#define	MAXSTR		10
#define MAXRULES    100
#define MAXINVARS   4
#define	MAXOUTVARS	4

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

enum MF_TYPE { TRIANGULAR = 0, TRAPEZOIDAL };
enum DEFUZZIFICATION { COG = 0, CA };
enum T_NORM { MIN = 0, PROD };

#endif // !__DEFINES_H__

