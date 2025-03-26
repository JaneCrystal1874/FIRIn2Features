// File: feature_extractor_tb.cpp
#include "FIRIn2Features.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

//--------- �����ļ�·�� ---------
const char INPUT_DATA_FILE[] = "input_waveform.dat";   // �����ź������ļ�
const char OUTPUT_FEATURE_FILE[] = "output_features.txt"; // ��������ļ�
const int FIR_OUTPUT_FREQ = 250;       // FIRʱ��Ƶ�ʣ�Hz��
const int PHYS_MAX_PERIOD = 1;      // ���������������ڣ��룩
const int CIRCULAR_BUF_SIZE = 512;     // ѭ�����泤�ȣ�������2^N��
const int NORMALIZED_POINTS = 200;     // ��һ������

//-------- ���ݼ��غ��� ----------
int load_input_data(const char* filename, std::vector<float>& data_buffer) {
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cerr << "�����޷��������ļ� " << filename << std::endl;
        return -1;
    }

    float val;
    while (in_file >> val) {          // ���ж�ȡ������ֵ
        data_buffer.push_back(val);
    }
    in_file.close();

    // ������ݳ����Ƿ����Ԥ��
    if (data_buffer.size() != CIRCULAR_BUF_SIZE) {
        std::cerr << "���棺�������ݳ���(" << data_buffer.size()
                  << ") ��Ԥ��(" << CIRCULAR_BUF_SIZE << ") ��ƥ��" << std::endl;
    }
    return 0;
}

//-------- �����Ժ��� -----------
int main() {
    // ��ʼ��������
    hls::stream<float> fir_input_stream;
    hls::stream<float> feature_output_stream;

    // �������벨������
    std::vector<float> input_waveform;
    if (load_input_data(INPUT_DATA_FILE, input_waveform) != 0) {
        return 1;
    }

    //--------- ����д������ ---------
    std::cout << "����д��" << input_waveform.size() << "��������..." << std::endl;
    for (const auto& val : input_waveform) {
        fir_input_stream << val;          // ������д��HLS��
    }

    //--------- ִ����� ---------
    std::cout << "��ʼִ��������ȡ..." << std::endl;
    feature_extractor_ip(fir_input_stream, feature_output_stream);

    //--------- ������� ---------
    std::ofstream out_file(OUTPUT_FEATURE_FILE);
    if (!out_file.is_open()) {
        std::cerr << "�����޷���������ļ�" << std::endl;
        return 1;
    }

    // ��ȡ�����������������ÿ����������ĸ�������
    int feature_count = 0;
    while (!feature_output_stream.empty()) {
        float aip, slope, tdia, sip;
        feature_output_stream >> aip;     // ��ȡ����˳�������д��˳��һ��
        feature_output_stream >> slope;
        feature_output_stream >> tdia;
        feature_output_stream >> sip;

        // д���ļ��Ϳ���̨
        out_file << "Feature_Set:" << feature_count << "\n"
                 << "AIP: " << aip << "\n"
                 << "Slope: " << slope << "\n"
                 << "TDIA: " << tdia << "\n"
                 << "SIP: " << sip << "\n\n";

        std::cout << "�������� #" << feature_count++ << ":\n"
                  << "  AIP(�յ��ֵ): " << aip << "\n"
                  << "  Slope(б��):   " << slope << "\n"
                  << "  TDIA(��λ��):  " << tdia << "\n"
                  << "  SIP(�������): " << sip << "\n"
                  << "------------------------" << std::endl;
    }

    out_file.close();
    std::cout << "\n������ɣ�����ѱ�����: " << OUTPUT_FEATURE_FILE << std::endl;
    return 0;
}
