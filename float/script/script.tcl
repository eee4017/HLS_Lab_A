############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fft_ac
set_top fft_fixed
add_files fft_ac/solution1/fft_fixed.cpp
add_files fft_ac/solution1/fft_fixed.h
add_files fft_ac/solution1/utils.cpp
add_files fft_ac/solution1/utils.h
add_files -tb fft_ac/solution1/fft_fixed_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7k70t-fbv676-1}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog -vivado_optimization_level 2 -vivado_phys_opt place -vivado_report_level 0
source "./fft_ac/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all -tool xsim
export_design -flow impl -rtl verilog -format ip_catalog
