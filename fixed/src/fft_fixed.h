#ifndef SRC_FILES_FFT_FIXED_H_
#define SRC_FILES_FFT_FIXED_H_

#include "ac_int.h"
#include <math.h>
#include <complex>
#include <ap_fixed.h>
using namespace std;

#define BUTTERFLY


#define FIXED
#ifdef FIXED

const int int_width=8;
const int width=24;
typedef ap_fixed<width,int_width > dType;
typedef ap_fixed<width,int_width > mType;
typedef ap_fixed<width,int_width > tType;

#else

typedef double dType;
typedef double bType;
typedef double mType;
typedef double tType;

#endif


const int FFT_SIZE = 64;
const int FFT_STAGES = 6;
const int MASK_BITS = FFT_STAGES-1;
const double pi = 3.14159265358979363846;

typedef complex< dType > data_d_comp;

typedef ap_fixed<64,8> cType;
typedef complex< cType > c_data;

void fft_fixed(data_d_comp x_l[FFT_SIZE/2], data_d_comp x_u[FFT_SIZE/2]);

#endif /* SRC_FILES_FFT_FIXED_H_ */
