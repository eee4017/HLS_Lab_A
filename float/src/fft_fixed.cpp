
#include "fft_fixed.h"
#include "utils.h"



void fft_fixed(ac_complex<dType > x_l[FFT_SIZE/2], ac_complex<dType > x_u[FFT_SIZE/2])
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
#ifdef BUTTERFLY
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
#else
				idx_u = idx_l^(-1<<i);
				data_l = x_l[idx_l];
				data_u = x_u[idx_u];
//				swap(addr_mask>>1, idx_l, data_l, data_u);
				t = complex_mult(twiddle(j * idx) ,data_u);
				x_tmp = data_l;
				data_u = scale(x_tmp - t);
				data_l = scale(x_tmp + t);
//				swap(addr_mask, idx_l, data_l, data_u);
				x_u[idx_u] = data_u;
				x_l[idx_l] = data_l;
				k+=n2;
				idx_l += (1<<i);
				if (idx_l[FFT_STAGES-1]) {//if idx overflows, wrap
					idx_l[FFT_STAGES-1] = 0;
					idx_l += 1;
				}
#endif

				if (k>=FFT_SIZE-1)
					break;
			}
		if(j==n1-1)
			break;
		}
		addr_mask <<= 1;
	}
}
