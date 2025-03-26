#ifndef FIR2F_H
#define FIR2F_H
#include "hls_stream.h"
#include "hls_math.h"
#include "ap_int.h"
void feature_extractor_ip(hls::stream<float>& fir_in,
    hls::stream<float>& features_out);


#endif
