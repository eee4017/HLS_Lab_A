#include "utils.h"

using namespace std;

void swap(int addr_mask, int idx_l, complex<dType > &data_l, complex<dType > &data_u){
	complex<dType > data_l_tmp;
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


complex<tType> twiddle(int n){
	complex<tType> tmp;

	tmp.real( cos_lookup(n) );
	tmp.imag( -sin_lookup(n) );
	return tmp;
}


#pragma map_to_operator
complex<mType > complex_mult (complex<tType > twiddle, complex<dType > data) {
	tType a,b;
	dType c,d;
	mType e;
	complex<mType > tmp;
	a = twiddle.real();
	b = twiddle.imag();
	c = data.real();
	d = data.imag();

	e = a*(c-d);
	tmp.real( d*(a-b) + e );
	tmp.imag( c*(a+b) - e );
	return tmp;
}

complex<dType > scale (complex<mType > data) {
	complex<mType > tmp;
	tmp = data;
#ifdef FIXED
	tmp.real( tmp.real()>>1 );
	tmp.imag( tmp.imag()>>1 );
#else
	tmp.real( tmp.real() / 2 );
	tmp.imag( tmp.imag() / 2 );
#endif
	return tmp;
}
