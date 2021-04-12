/*
 * fft_fixed.h
 *
 *  Created on: 2021¦~4¤ë9¤é
 *      Author: user
 */

#ifndef SRC_FILES_FFT_FIXED_H_
#define SRC_FILES_FFT_FIXED_H_

#include "ac_fixed.h"
#include "ac_complex.h"
#include "ac_int.h"

//#define BUTTERFLY
//#define COMPLEX_MUL
#define LOOKUP

//#define FIXED
#ifdef FIXED

typedef ac_fixed<14,2 > dType;
typedef ac_fixed<29,5 > mType;
typedef ac_fixed<15,2 > tType;

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


void fft_fixed(ac_complex<dType > x_l[FFT_SIZE/2], ac_complex<dType > x_u[FFT_SIZE/2]);


#endif /* SRC_FILES_FFT_FIXED_H_ */
