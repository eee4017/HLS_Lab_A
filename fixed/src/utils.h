#ifndef SRC_FILES_UTILS_H_
#define SRC_FILES_UTILS_H_
#include "fft_fixed.h"

using namespace std;

void swap(int addr_mask, int idx_l, complex<dType > &data_l, complex<dType > &data_u);
tType sin_lookup (int n);
tType cos_lookup (int n);
complex<tType> twiddle(int n);
complex<mType > complex_mult (complex<tType > twiddle, complex<dType > data);
complex<dType > scale (complex<mType > data);


#endif /* SRC_FILES_UTILS_H_ */
