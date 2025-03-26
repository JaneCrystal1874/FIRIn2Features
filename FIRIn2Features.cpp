#include "FIRIn2Features.h"

//----------- �������� ------------
const int FIR_OUTPUT_FREQ = 250;       // FIRʱ��Ƶ�ʣ�Hz��
const int PHYS_MAX_PERIOD = 1;      // ���������������ڣ��룩
const int CIRCULAR_BUF_SIZE = 512;     // ѭ�����泤�ȣ�������2^N��
const int NORMALIZED_POINTS = 200;     // ��һ������

// �������N��������Ļ�״����
struct CircularBuffer {
    float buffer[CIRCULAR_BUF_SIZE];
    ap_uint<10> wr_ptr = 0; // ֧�����1024����

    void write(float data) {
        buffer[wr_ptr] = data;
        wr_ptr++;
        if(wr_ptr >= CIRCULAR_BUF_SIZE) wr_ptr = 0;
    }

    float read(int idx) {
        return buffer[(wr_ptr - idx + CIRCULAR_BUF_SIZE) % CIRCULAR_BUF_SIZE];
    }
};

// ��ֵ���
void peak_detection(hls::stream<float>& in, hls::stream<ap_uint<10> >& peak_loc_stream)
{
    CircularBuffer buf;
    const int MIN_PEAK_DIST = 110; // 55 samples

    while(!in.empty()) {
        // ����д�뻷״����
        float data = in.read();
        buf.write(data);

        // ����Ƿ�Ϊ��ֵ����Ҫ�۲�ǰ�󴰿ڣ�
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

        //�����peak_loc_stream����ǵ�ǰ�����������й�ֵ����buffer�е�����
        if(is_valley) {
            peak_loc_stream << curr_idx;
        }
    }
}

// ���ڻ������һ��
void interval_normalization(hls::stream<ap_uint<10> >& peaks,hls::stream<float>& normalized_out)
{
    CircularBuffer buf;
    ap_uint<10> last_peak = 0;

    while(!peaks.empty())
    {
        ap_uint<10> curr_peak;
        peaks >> curr_peak;

        // �������ڳ��ȣ������ε�ַ��
        int interval_len;
        if(curr_peak > last_peak)
        {
        	interval_len = curr_peak - last_peak;
        }
        else
        {
        	interval_len =  (CIRCULAR_BUF_SIZE + curr_peak - last_peak);
        }

        // ����������Ч����
        if(interval_len > PHYS_MAX_PERIOD * FIR_OUTPUT_FREQ) continue;


        //�ײ�����

        // ���Բ�ֵ��һ��
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

// ������ȡ����
void compute_features(hls::stream<float>& normalized_in,
		hls::stream<float>& features_out)
{
    float buffer[NORMALIZED_POINTS];

    // �����һ������
    for(int i = 0; i < NORMALIZED_POINTS; ++i) {
        normalized_in >> buffer[i];
    }

    // ��ּ���
    float diff1[NORMALIZED_POINTS-1];
    for(int i = 0; i < NORMALIZED_POINTS-1; ++i) {
        diff1[i] = buffer[i+1] - buffer[i];
    }

    // ����������
    float aip = 0, slope_ip = 0;
    float tdia = 0, sip = 0;

    // �������ŷ壨��100�㣩
    for(int i = 100; i < NORMALIZED_POINTS; ++i) {
        if(buffer[i] > buffer[(int)tdia])
            tdia = i;
    }

    // ���ҹյ㣨20-99���䣩
    for(int i = 20; i < 99; ++i) {
        if(diff1[i] < slope_ip) {
            slope_ip = diff1[i];
            aip = buffer[i];
        }
    }
    slope_ip = -slope_ip; // ��������

    // ����������������η���
    for(int i = 0; i < tdia; ++i) {
        sip += (buffer[i] + buffer[i+1]) * 0.5f;
    }


    //��һ��������һ����������matlab��¼,���Ǳ߲�̫һ��������һ��
    aip = aip * 4;
    slope_ip = slope_ip * 108.384518;
    tdia = (tdia - 101) * 0.01;
    sip = (sip - 0.1056) * 0.05;

    // ���˳��[aip, slope_ip, tdia, sip]
    features_out << aip;
    features_out << slope_ip;
    features_out << tdia;
    features_out << sip;
}

// ���㹦�ܼ���
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
