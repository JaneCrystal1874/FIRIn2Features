#include "FIRIn2Features.h"

//----------- 参数配置 ------------
const int FIR_OUTPUT_FREQ = 250;       // FIR时钟频率（Hz）
const int PHYS_MAX_PERIOD = 1;      // 允许的最大生理周期（秒）
const int CIRCULAR_BUF_SIZE = 512;     // 循环缓存长度（必须是2^N）
const int NORMALIZED_POINTS = 200;     // 归一化点数

// 保存最近N个采样点的环状缓存
struct CircularBuffer {
    float buffer[CIRCULAR_BUF_SIZE];
    ap_uint<10> wr_ptr = 0; // 支持最大1024长度

    void write(float data) {
        buffer[wr_ptr] = data;
        wr_ptr++;
        if(wr_ptr >= CIRCULAR_BUF_SIZE) wr_ptr = 0;
    }

    float read(int idx) {
        return buffer[(wr_ptr - idx + CIRCULAR_BUF_SIZE) % CIRCULAR_BUF_SIZE];
    }
};

// 峰值检测
void peak_detection(hls::stream<float>& in, hls::stream<ap_uint<10> >& peak_loc_stream)
{
    CircularBuffer buf;
    const int MIN_PEAK_DIST = 110; // 55 samples

    while(!in.empty()) {
        // 持续写入环状缓存
        float data = in.read();
        buf.write(data);

        // 检测是否为谷值（需要观察前后窗口）
        bool is_valley = true;
        int curr_idx = buf.wr_ptr;

        for(int i = 1; i <= MIN_PEAK_DIST; i++) {
            float prev = buf.read(curr_idx - i);
            float next = buf.read(curr_idx + i);
            if(data >= prev || data >= next) {
                is_valley = false;
                break;
            }
        }

        //输出流peak_loc_stream存的是当前输入流中所有谷值的在buffer中的索引
        if(is_valley) {
            peak_loc_stream << curr_idx;
        }
    }
}

// 周期划分与归一化
void interval_normalization(hls::stream<ap_uint<10> >& peaks,hls::stream<float>& normalized_out)
{
    CircularBuffer buf;
    ap_uint<10> last_peak = 0;

    while(!peaks.empty())
    {
        ap_uint<10> curr_peak;
        peaks >> curr_peak;

        // 计算周期长度（处理环形地址）
        int interval_len;
        if(curr_peak > last_peak)
        {
        	interval_len = curr_peak - last_peak;
        }
        else
        {
        	interval_len =  (CIRCULAR_BUF_SIZE + curr_peak - last_peak);
        }

        // 舍弃过长无效周期
        if(interval_len > PHYS_MAX_PERIOD * FIR_OUTPUT_FREQ) continue;


        //底部对齐

        // 线性插值归一化
        for(int i = 0; i < NORMALIZED_POINTS; ++i) {
            float pos = (float)interval_len * i / NORMALIZED_POINTS;
            int idx_0 = last_peak + (int)pos;
            int idx_1 = idx_0 + 1;

            float v0 = buf.read(idx_0);
            float v1 = buf.read(idx_1);
            float interp_val = v0 + (v1 - v0)*(pos - (int)pos);

            normalized_out << interp_val;
        }

        last_peak = curr_peak;
    }
}

// 特征提取核心
void compute_features(hls::stream<float>& normalized_in,
		hls::stream<float>& features_out)
{
    float buffer[NORMALIZED_POINTS];

    // 缓存归一化周期
    for(int i = 0; i < NORMALIZED_POINTS; ++i) {
        normalized_in >> buffer[i];
    }

    // 差分计算
    float diff1[NORMALIZED_POINTS-1];
    for(int i = 0; i < NORMALIZED_POINTS-1; ++i) {
        diff1[i] = buffer[i+1] - buffer[i];
    }

    // 特征计算结果
    float aip = 0, slope_ip = 0;
    float tdia = 0, sip = 0;

    // 查找舒张峰（后100点）
    for(int i = 100; i < NORMALIZED_POINTS; ++i) {
        if(buffer[i] > buffer[(int)tdia])
            tdia = i;
    }

    // 查找拐点（20-99区间）
    for(int i = 20; i < 99; ++i) {
        if(diff1[i] < slope_ip) {
            slope_ip = diff1[i];
            aip = buffer[i];
        }
    }
    slope_ip = -slope_ip; // 调整符号

    // 计算面积特征（梯形法则）
    for(int i = 0; i < tdia; ++i) {
        sip += (buffer[i] + buffer[i+1]) * 0.5f;
    }


    //归一化处理，归一化参数来自matlab记录,跟那边不太一样，调了一下
    aip = aip * 4;
    slope_ip = slope_ip * 108.384518;
    tdia = (tdia - 101) * 0.01;
    sip = (sip - 0.1056) * 0.05;

    // 输出顺序：[aip, slope_ip, tdia, sip]
    features_out << aip;
    features_out << slope_ip;
    features_out << tdia;
    features_out << sip;
}

// 顶层功能集成
void feature_extractor_ip(hls::stream<float>& fir_in,
    hls::stream<float>& features_out)
{
#pragma HLS INTERFACE axis port=fir_in
#pragma HLS INTERFACE axis port=features_out
#pragma HLS DATAFLOW

    hls::stream<ap_uint<10> > peak_loc_stream;
    hls::stream<float> normalized_stream;

    peak_detection(fir_in, peak_loc_stream);
    interval_normalization(peak_loc_stream, normalized_stream);
    compute_features(normalized_stream, features_out);
}
