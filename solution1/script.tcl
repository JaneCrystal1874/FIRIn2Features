############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project FIRIn2Features
set_top feature_extractor_ip
add_files FIRIn2Features/FIRIn2Features.h
add_files FIRIn2Features/FIRIn2Features.cpp
add_files -tb FIRIn2Features/input_waveform.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb FIRIn2Features/FIRIn2Features_testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020-clg400-2} -tool vivado
create_clock -period 10 -name default
config_export -description features_extractor -format ip_catalog -rtl verilog
#source "./FIRIn2Features/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -description "features_extractor"
