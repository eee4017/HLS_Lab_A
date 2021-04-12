/*
 * utils.cpp
 *
 *  Created on: 2021¦~4¤ë9¤é
 *      Author: user
 */

#include "utils.h"
#include <hls_math.h>

void swap(int addr_mask, int idx_l, ac_complex<dType > &data_l, ac_complex<dType > &data_u){
	ac_complex<dType > data_l_tmp;
	bool swap_d;
	data_l_tmp = data_l;
	swap_d = (addr_mask & idx_l);
	data_l = swap_d ? data_u : data_l;
	data_u = swap_d ? data_l_tmp : data_u;
}


tType sin_lookup (int n) {
	tType sin_table[FFT_SIZE/4+1] = {
		#include "sin_qtable.txt"
	};
	tType tmp;
	int idx;
	bool sign;
	if (n<=FFT_SIZE/4){
		idx = n;
		sign = 0;
	}
	else if (n<FFT_SIZE/2) {
		idx = FFT_SIZE/4-n%(FFT_SIZE/4);
		sign = 0;
	}
	else if (n<3*FFT_SIZE/4) {
		idx = n%(FFT_SIZE/4);
		sign = 1;
	}
	else {
		idx = FFT_SIZE/4-n%(FFT_SIZE/4);
		sign = 1;
	}
	return sign ? (tType)-sin_table[idx] : (tType)sin_table[idx];
}

tType cos_lookup (int n) {
	tType cos_table[FFT_SIZE/4+1] = {
		#include "cos_qtable.txt"
	};
	tType tmp;
	int idx;
	bool sign;
	if (n<=FFT_SIZE/4) {
		idx = n;
		sign = 0;
	}
	else if (n<FFT_SIZE/2) {
		idx = FFT_SIZE/4-n%(FFT_SIZE/4);
		sign = 1;
	}
	else if (n<3*FFT_SIZE/4) {
		idx = n%(FFT_SIZE/4);
		sign = 1;
	}
	else {
		idx = FFT_SIZE/4-n%(FFT_SIZE/4);
		sign = 0;
	}
	return sign ? (tType)-cos_table[idx] : (tType)cos_table[idx];
}


ac_complex<tType> twiddle(int n){
	ac_complex<tType> tmp;
#ifdef LOOKUP
	tmp.r() = cos_lookup(n);
	tmp.i() = -sin_lookup(n);
#else
	tmp.r() = cos(2 * M_PI * n / FFT_SIZE);
	tmp.i() = -sin(2 * M_PI * n / FFT_SIZE);
#endif
	return tmp;
}


#pragma map_to_operator
ac_complex<mType > complex_mult (ac_complex<tType > twiddle, ac_complex<dType > data) {
#ifdef COMPLEX_MUL
	tType a,b;
	dType c,d;
	mType e;
	ac_complex<mType > tmp;
	a = twiddle.r();
	b = twiddle.i();
	c = data.r();
	d = data.i();

	e = a*(c-d);
	tmp.r() = d*(a-b) + e;
	tmp.i() = c*(a+b) - e;
	return tmp;
#else
	return twiddle * data;
#endif
}

ac_complex<dType > scale (ac_complex<mType > data) {
	ac_complex<mType > tmp;
	tmp = data;
#ifdef FIXED
	tmp.r() = tmp.r()>>1;
	tmp.i() = tmp.i()>>1;
#else
	tmp.r() = tmp.r() / 2;
	tmp.i() = tmp.i() / 2;
#endif
	return tmp;
}
