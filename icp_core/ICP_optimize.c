/*
 * ICP_optimize.c
 *
 *  Created on: 2013/01/17
 *      Author: RyzeVia
 *
 *  *optimization algorithm definition
 *   This file use Newton method with exponential distribution
 */
//#define DEBUG_ENABLE
//#define DEBUG_LEVEL 60

#include "libicp.h"

#define NEWTON_MAX 100000
#define NEWTON_EPS 1.0e-5
#define NEWTON_START 1.
#define NEWTON_GIVEUP	10

static double f_opt(double time, double fr, double ctime){
	return  exp(fr*(time+ctime))*(1 - fr * time) - 1;
}

static double df_opt(double time, double fr, double ctime){
	//double fst = fr * fr * time;

	return -fr * fr * time * exp( fr * (ctime+time));
}

static int newton(double calc_time, double fr, double cp_time, double *result){
	int iter = 0;
	int done = 0;
//	double cand = calc_time;
	double cand = 1/fr;
	double fo;
	double dfo;
	*result = 0;


	while(!done){
		iter++;
		fo = f_opt(cand, fr, cp_time);
		dfo = df_opt(cand, fr, cp_time);
		*result = cand - fo / dfo;

		if(fabs(*result - cand)  < NEWTON_EPS){
			done = 1;
		}
		cand = *result;

		if(!done && (iter > NEWTON_MAX)){
			return -1;
		}
	}


	return iter;
}

void ICP_opt_get_iter(double fr, int iter, struct timespec *calc, struct timespec *cp, int *iter_offset, int *iter_stride){
	double d_calc = ts2dbl(calc);
	double d_cp = ts2dbl(cp);
	double result;
//	double init = NEWTON_START;
	char *cpprint;
//	int done = 0;
	ICP_PRE_PROC(__FUNCTION__);

	cpprint = CFR_getvalue("ICP_TEST_CHK_CPOPT", NULL);
	if(cpprint != NULL){
		fprintf(stderr, "cp was %d, %ld (%f)\n", TSPRINTF(cp), ts2dbl(cp));
		fprintf(stderr, "optimized by calc:%f cp:%f fr:%f\n", d_calc, d_cp, fr);
	}

	if(newton(d_calc, fr, d_cp, &result) == -1){
		ERRORF("Optimized Iter cannot converge.\n");
	}

	*iter_offset = iter;
	*iter_stride = (int)ceil(result / d_calc);


	ICP_POST_PROC(__FUNCTION__);

}


