// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _peak_detection_HH_
#define _peak_detection_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "feature_extractorcud.h"
#include "peak_detection_bubkb.h"

namespace ap_rtl {

struct peak_detection : public sc_module {
    // Port declarations 16
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_in< sc_logic > start_full_n;
    sc_out< sc_logic > ap_done;
    sc_in< sc_logic > ap_continue;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_logic > start_out;
    sc_out< sc_logic > start_write;
    sc_in< sc_lv<32> > in_V_TDATA;
    sc_in< sc_logic > in_V_TVALID;
    sc_out< sc_logic > in_V_TREADY;
    sc_out< sc_lv<10> > peak_loc_stream_V_V_din;
    sc_in< sc_logic > peak_loc_stream_V_V_full_n;
    sc_out< sc_logic > peak_loc_stream_V_V_write;
    sc_signal< sc_logic > ap_var_for_const0;
    sc_signal< sc_lv<5> > ap_var_for_const1;


    // Module declarations
    peak_detection(sc_module_name name);
    SC_HAS_PROCESS(peak_detection);

    ~peak_detection();

    sc_trace_file* mVcdFile;

    peak_detection_bubkb* buf_buffer_U;
    feature_extractorcud<1,2,32,32,1>* feature_extractorcud_U1;
    feature_extractorcud<1,2,32,32,1>* feature_extractorcud_U2;
    sc_signal< sc_logic > real_start;
    sc_signal< sc_logic > start_once_reg;
    sc_signal< sc_logic > ap_done_reg;
    sc_signal< sc_lv<6> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_logic > internal_ap_ready;
    sc_signal< sc_logic > in_V_TDATA_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<1> > tmp_nbreadreq_fu_90_p3;
    sc_signal< sc_logic > peak_loc_stream_V_V_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_lv<1> > icmp_ln40_fu_238_p2;
    sc_signal< sc_lv<32> > tmp_9_reg_450;
    sc_signal< bool > ap_block_state2;
    sc_signal< sc_lv<9> > buf_wr_ptr_V_fu_204_p3;
    sc_signal< sc_lv<9> > buf_wr_ptr_V_reg_456;
    sc_signal< sc_lv<10> > tmp_V_1_fu_212_p1;
    sc_signal< sc_lv<10> > tmp_V_1_reg_461;
    sc_signal< sc_lv<11> > zext_ln215_fu_216_p1;
    sc_signal< sc_lv<11> > zext_ln215_reg_467;
    sc_signal< sc_lv<32> > bitcast_ln43_fu_220_p1;
    sc_signal< sc_lv<32> > bitcast_ln43_reg_472;
    sc_signal< sc_lv<1> > icmp_ln43_1_fu_228_p2;
    sc_signal< sc_lv<1> > icmp_ln43_1_reg_477;
    sc_signal< sc_lv<1> > icmp_ln40_reg_482;
    sc_signal< bool > ap_block_state3;
    sc_signal< sc_lv<11> > select_ln1372_fu_308_p3;
    sc_signal< sc_lv<11> > select_ln1372_reg_486;
    sc_signal< sc_lv<1> > or_ln43_fu_331_p2;
    sc_signal< sc_lv<1> > or_ln43_reg_491;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_lv<32> > buf_buffer_q0;
    sc_signal< sc_logic > ap_CS_fsm_state5;
    sc_signal< sc_lv<32> > buf_buffer_q1;
    sc_signal< sc_lv<1> > icmp_ln43_2_fu_363_p2;
    sc_signal< sc_lv<1> > icmp_ln43_2_reg_517;
    sc_signal< sc_lv<1> > icmp_ln43_3_fu_369_p2;
    sc_signal< sc_lv<1> > icmp_ln43_3_reg_522;
    sc_signal< sc_lv<1> > icmp_ln43_4_fu_393_p2;
    sc_signal< sc_lv<1> > icmp_ln43_4_reg_527;
    sc_signal< sc_lv<1> > icmp_ln43_5_fu_399_p2;
    sc_signal< sc_lv<1> > icmp_ln43_5_reg_532;
    sc_signal< sc_lv<7> > i_fu_441_p2;
    sc_signal< sc_logic > ap_CS_fsm_state6;
    sc_signal< sc_lv<1> > or_ln43_3_fu_435_p2;
    sc_signal< sc_lv<9> > buf_buffer_address0;
    sc_signal< sc_logic > buf_buffer_ce0;
    sc_signal< sc_logic > buf_buffer_we0;
    sc_signal< sc_lv<9> > buf_buffer_address1;
    sc_signal< sc_logic > buf_buffer_ce1;
    sc_signal< sc_lv<9> > t_V_reg_142;
    sc_signal< bool > ap_block_state1;
    sc_signal< sc_lv<7> > i_0_reg_153;
    sc_signal< sc_lv<64> > zext_ln544_fu_175_p1;
    sc_signal< sc_lv<64> > zext_ln544_1_fu_336_p1;
    sc_signal< sc_lv<64> > sext_ln544_fu_341_p1;
    sc_signal< sc_lv<10> > zext_ln112_fu_180_p1;
    sc_signal< sc_lv<10> > add_ln700_fu_184_p2;
    sc_signal< sc_lv<1> > tmp_2_fu_196_p3;
    sc_signal< sc_lv<9> > add_ln891_fu_190_p2;
    sc_signal< sc_lv<23> > trunc_ln43_fu_224_p1;
    sc_signal< sc_lv<10> > zext_ln40_fu_234_p1;
    sc_signal< sc_lv<10> > add_ln42_fu_244_p2;
    sc_signal< sc_lv<11> > zext_ln215_1_fu_249_p1;
    sc_signal< sc_lv<11> > ret_V_fu_253_p2;
    sc_signal< sc_lv<11> > ret_V_1_fu_258_p2;
    sc_signal< sc_lv<9> > trunc_ln1372_fu_272_p1;
    sc_signal< sc_lv<9> > trunc_ln1372_1_fu_284_p1;
    sc_signal< sc_lv<9> > sub_ln1372_fu_288_p2;
    sc_signal< sc_lv<11> > p_and_t_fu_294_p3;
    sc_signal< sc_lv<1> > tmp_6_fu_264_p3;
    sc_signal< sc_lv<11> > sub_ln1372_1_fu_302_p2;
    sc_signal< sc_lv<11> > p_and_f_fu_276_p3;
    sc_signal< sc_lv<8> > tmp_3_fu_316_p4;
    sc_signal< sc_lv<1> > icmp_ln43_fu_325_p2;
    sc_signal< sc_lv<32> > bitcast_ln43_1_fu_345_p1;
    sc_signal< sc_lv<8> > tmp_4_fu_349_p4;
    sc_signal< sc_lv<23> > trunc_ln43_1_fu_359_p1;
    sc_signal< sc_lv<32> > bitcast_ln43_2_fu_375_p1;
    sc_signal< sc_lv<8> > tmp_7_fu_379_p4;
    sc_signal< sc_lv<23> > trunc_ln43_2_fu_389_p1;
    sc_signal< sc_lv<1> > or_ln43_1_fu_405_p2;
    sc_signal< sc_lv<1> > and_ln43_fu_409_p2;
    sc_signal< sc_lv<1> > grp_fu_165_p2;
    sc_signal< sc_lv<1> > or_ln43_2_fu_420_p2;
    sc_signal< sc_lv<1> > and_ln43_2_fu_424_p2;
    sc_signal< sc_lv<1> > grp_fu_170_p2;
    sc_signal< sc_lv<1> > and_ln43_1_fu_414_p2;
    sc_signal< sc_lv<1> > and_ln43_3_fu_429_p2;
    sc_signal< sc_lv<6> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<6> ap_ST_fsm_state1;
    static const sc_lv<6> ap_ST_fsm_state2;
    static const sc_lv<6> ap_ST_fsm_state3;
    static const sc_lv<6> ap_ST_fsm_state4;
    static const sc_lv<6> ap_ST_fsm_state5;
    static const sc_lv<6> ap_ST_fsm_state6;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<32> ap_const_lv32_4;
    static const sc_lv<32> ap_const_lv32_5;
    static const sc_lv<9> ap_const_lv9_0;
    static const sc_lv<7> ap_const_lv7_1;
    static const sc_lv<10> ap_const_lv10_1;
    static const sc_lv<9> ap_const_lv9_1;
    static const sc_lv<32> ap_const_lv32_9;
    static const sc_lv<23> ap_const_lv23_0;
    static const sc_lv<7> ap_const_lv7_6F;
    static const sc_lv<11> ap_const_lv11_200;
    static const sc_lv<32> ap_const_lv32_A;
    static const sc_lv<2> ap_const_lv2_0;
    static const sc_lv<11> ap_const_lv11_0;
    static const sc_lv<32> ap_const_lv32_17;
    static const sc_lv<32> ap_const_lv32_1E;
    static const sc_lv<8> ap_const_lv8_FF;
    static const sc_lv<5> ap_const_lv5_3;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_var_for_const0();
    void thread_ap_var_for_const1();
    void thread_ap_clk_no_reset_();
    void thread_add_ln42_fu_244_p2();
    void thread_add_ln700_fu_184_p2();
    void thread_add_ln891_fu_190_p2();
    void thread_and_ln43_1_fu_414_p2();
    void thread_and_ln43_2_fu_424_p2();
    void thread_and_ln43_3_fu_429_p2();
    void thread_and_ln43_fu_409_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_CS_fsm_state5();
    void thread_ap_CS_fsm_state6();
    void thread_ap_block_state1();
    void thread_ap_block_state2();
    void thread_ap_block_state3();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_bitcast_ln43_1_fu_345_p1();
    void thread_bitcast_ln43_2_fu_375_p1();
    void thread_bitcast_ln43_fu_220_p1();
    void thread_buf_buffer_address0();
    void thread_buf_buffer_address1();
    void thread_buf_buffer_ce0();
    void thread_buf_buffer_ce1();
    void thread_buf_buffer_we0();
    void thread_buf_wr_ptr_V_fu_204_p3();
    void thread_i_fu_441_p2();
    void thread_icmp_ln40_fu_238_p2();
    void thread_icmp_ln43_1_fu_228_p2();
    void thread_icmp_ln43_2_fu_363_p2();
    void thread_icmp_ln43_3_fu_369_p2();
    void thread_icmp_ln43_4_fu_393_p2();
    void thread_icmp_ln43_5_fu_399_p2();
    void thread_icmp_ln43_fu_325_p2();
    void thread_in_V_TDATA_blk_n();
    void thread_in_V_TREADY();
    void thread_internal_ap_ready();
    void thread_or_ln43_1_fu_405_p2();
    void thread_or_ln43_2_fu_420_p2();
    void thread_or_ln43_3_fu_435_p2();
    void thread_or_ln43_fu_331_p2();
    void thread_p_and_f_fu_276_p3();
    void thread_p_and_t_fu_294_p3();
    void thread_peak_loc_stream_V_V_blk_n();
    void thread_peak_loc_stream_V_V_din();
    void thread_peak_loc_stream_V_V_write();
    void thread_real_start();
    void thread_ret_V_1_fu_258_p2();
    void thread_ret_V_fu_253_p2();
    void thread_select_ln1372_fu_308_p3();
    void thread_sext_ln544_fu_341_p1();
    void thread_start_out();
    void thread_start_write();
    void thread_sub_ln1372_1_fu_302_p2();
    void thread_sub_ln1372_fu_288_p2();
    void thread_tmp_2_fu_196_p3();
    void thread_tmp_3_fu_316_p4();
    void thread_tmp_4_fu_349_p4();
    void thread_tmp_6_fu_264_p3();
    void thread_tmp_7_fu_379_p4();
    void thread_tmp_V_1_fu_212_p1();
    void thread_tmp_nbreadreq_fu_90_p3();
    void thread_trunc_ln1372_1_fu_284_p1();
    void thread_trunc_ln1372_fu_272_p1();
    void thread_trunc_ln43_1_fu_359_p1();
    void thread_trunc_ln43_2_fu_389_p1();
    void thread_trunc_ln43_fu_224_p1();
    void thread_zext_ln112_fu_180_p1();
    void thread_zext_ln215_1_fu_249_p1();
    void thread_zext_ln215_fu_216_p1();
    void thread_zext_ln40_fu_234_p1();
    void thread_zext_ln544_1_fu_336_p1();
    void thread_zext_ln544_fu_175_p1();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif
