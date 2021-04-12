############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fft_0412_1922
set_top fft_fixed
add_files fft_0412_1922/solution1/cos_qtable.txt
add_files fft_0412_1922/solution1/fft_fixed.cpp
add_files fft_0412_1922/solution1/fft_fixed.h
add_files fft_0412_1922/solution1/sin_qtable.txt
add_files fft_0412_1922/solution1/utils.cpp
add_files fft_0412_1922/solution1/utils.h
add_files -tb fft_0412_1922/solution1/fft_fixed_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7k70t-fbv676-1}
create_clock -period 10 -name default
#source "./fft_0412_1922/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all -tool xsim
export_design -format ip_catalog
