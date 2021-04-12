/*
 * utils.h
 *
 *  Created on: 2021¦~4¤ë9¤é
 *      Author: user
 */

#ifndef SRC_FILES_UTILS_H_
#define SRC_FILES_UTILS_H_
#include "fft_fixed.h"

void swap(int addr_mask, int idx_l, ac_complex<dType > &data_l, ac_complex<dType > &data_u);
tType sin_lookup (int n);
tType cos_lookup (int n);
ac_complex<tType> twiddle(int n);
ac_complex<mType > complex_mult (ac_complex<tType > twiddle, ac_complex<dType > data);
ac_complex<dType > scale (ac_complex<mType > data);


#endif /* SRC_FILES_UTILS_H_ */
