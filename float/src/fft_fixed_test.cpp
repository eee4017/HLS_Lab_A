#include <random>
#include <iostream>
#include "fft_fixed.h"
#include "utils.h"
using namespace std;

void c_fft_fixed(ac_complex<dType > x_l[FFT_SIZE/2], ac_complex<dType > x_u[FFT_SIZE/2])
{
	ac_complex<dType > x_tmp,data_tmp, data_l, data_u;
	ac_complex<mType > t;
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
				swap(addr_mask>>1, idx_l, data_l, data_u);
				t = complex_mult(twiddle(j * idx) ,data_u);
				x_tmp = data_l;
				data_u = scale(x_tmp - t);
				data_l = scale(x_tmp + t);
				swap(addr_mask, idx_l, data_l, data_u);
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
	double lower_bound = -1e4;
	double upper_bound = 1e4;
	uniform_real_distribution<double> unif(lower_bound,upper_bound);
	default_random_engine re;

	ac_complex<dType > c_l[FFT_SIZE/2];
	ac_complex<dType > c_u[FFT_SIZE/2];

	ac_complex<dType > hls_l[FFT_SIZE/2];
	ac_complex<dType > hls_u[FFT_SIZE/2];

	for (int i = 0; i < FFT_SIZE/2; i++) {
		dType a(unif(re));
		dType b(unif(re));
		ac_complex<dType > c(a, b);
		c_l[i] = c_u[i] = c;
		hls_l[i] = hls_u[i] = c;
	}

	c_fft_fixed(c_l, c_u);
	fft_fixed(hls_l, hls_u);

	ac_complex<dType > error;
	for (int i = 0; i < FFT_SIZE/2; i++) {
		error = error + hls_l[i] - c_l[i];
		error = error + hls_u[i] - c_u[i];
	}
	cout << error << "\n";

	return 0;
}
