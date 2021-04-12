#include <random>
#include <iostream>
#include "fft_fixed.h"
#include "utils.h"
using namespace std;

void c_swap(int addr_mask, int idx_l, c_data &data_l, c_data &data_u){
	c_data data_l_tmp;
	bool swap_d;
	data_l_tmp = data_l;
	swap_d = (addr_mask & idx_l);
	data_l = swap_d ? data_u : data_l;
	data_u = swap_d ? data_l_tmp : data_u;
}

cType c_sin_lookup (int n) {
	cType sin_table[FFT_SIZE/4+1] = {
		#include "sin_qtable.txt"
	};
	cType tmp;
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
	return sign ? (cType)-sin_table[idx] : (cType)sin_table[idx];
}

cType c_cos_lookup (int n) {
	cType cos_table[FFT_SIZE/4+1] = {
		#include "cos_qtable.txt"
	};
	cType tmp;
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
	return sign ? (cType)-cos_table[idx] : (cType)cos_table[idx];
}


complex<cType> c_twiddle(int n){
	complex<cType> tmp;

	tmp.real( c_cos_lookup(n) );
	tmp.imag( -c_sin_lookup(n) );
	return tmp;
}


#pragma map_to_operator
complex<cType > c_complex_mult (complex<cType > twiddle, complex<cType > data) {
	cType a,b;
	cType c,d;
	cType e;
	complex<cType > tmp;
	a = twiddle.real();
	b = twiddle.imag();
	c = data.real();
	d = data.imag();

	e = a*(c-d);
	tmp.real( d*(a-b) + e );
	tmp.imag( c*(a+b) - e );
	return tmp;
}

complex<cType > c_scale (complex<cType > data) {
	complex<cType > tmp;
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

void c_fft_fixed(c_data x_l[FFT_SIZE/2], c_data x_u[FFT_SIZE/2])
{
	c_data x_tmp,data_tmp, data_l, data_u;
	c_data t;
	ac_int<FFT_STAGES+1, false > n1, n2;
	ac_int<FFT_STAGES+1, false > idx;
	ac_int<FFT_STAGES, false > addr_mask = 1;
	ac_int<FFT_STAGES, 0 > idx_l=0;
	ac_int<FFT_STAGES-1, 0 > idx_u = 0;

	n1 = 0;
	n2 = 1;
	idx = FFT_SIZE;
	for (int i=0;i< FFT_STAGES;i++) {//stage
		idx_l = 0;
		n1 = n2;
		n2 = n2 + n2;
		idx>>=1;
		for (int j=0;j< FFT_SIZE/2;j++) {//segment
			int k=j;
			for (int kk=0;kk<FFT_SIZE/2;kk++) {//butterfly
				idx_u = idx_l^(-1<<i);
				data_l = x_l[idx_l];
				data_u = x_u[idx_u];
				c_swap(addr_mask>>1, idx_l, data_l, data_u);
				t = c_complex_mult(c_twiddle(j * idx) ,data_u);
				x_tmp = data_l;
				data_u = c_scale(x_tmp - t);
				data_l = c_scale(x_tmp + t);
				c_swap(addr_mask, idx_l, data_l, data_u);
				x_u[idx_u] = data_u;
				x_l[idx_l] = data_l;
				k+=n2;
				idx_l += (1<<i);
				if (idx_l[FFT_STAGES-1]) {//if idx overflows, wrap
					idx_l[FFT_STAGES-1] = 0;
					idx_l += 1;
				}
				if (k>=FFT_SIZE-1)
					break;
			}
		if(j==n1-1)
			break;
		}
		addr_mask <<= 1;
	}
}

int main() {
	double lower_bound = -1e2;
	double upper_bound = 1e2;
	uniform_real_distribution<double> unif(lower_bound,upper_bound);
	default_random_engine re;

	static c_data c_l[FFT_SIZE/2];
	static c_data c_u[FFT_SIZE/2];

	static complex<dType > hls_l[FFT_SIZE/2];
	static complex<dType > hls_u[FFT_SIZE/2];

	for (int i = 0; i < FFT_SIZE/2; i++) {
		double a = unif(re);
		double b = unif(re);
		c_l[i].real((cType)a), c_u[i].imag((cType)b);
		hls_l[i].real((dType)a), hls_u[i].imag((dType)b);
	}

	c_fft_fixed(c_l, c_u);
	fft_fixed(hls_l, hls_u);

	double error=0;
	for (int i = 0; i < FFT_SIZE/2; i++) {
		double tmp_a = (hls_l[i].real().to_double() - c_l[i].real().to_double());
		double tmp_b = (hls_l[i].imag().to_double() - c_l[i].imag().to_double());
		double tmp_c = (hls_u[i].real().to_double() - c_u[i].real().to_double());
		double tmp_d = (hls_u[i].imag().to_double() - c_u[i].imag().to_double());

		error = error + fabs(tmp_a) + fabs(tmp_b) + fabs(tmp_c) + fabs(tmp_d);
	}
	cout << "Hello: " << error << "\n";

	return 0;
}
