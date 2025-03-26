// File: feature_extractor_tb.cpp
#include "FIRIn2Features.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

//--------- 配置文件路径 ---------
const char INPUT_DATA_FILE[] = "input_waveform.dat";   // 输入信号数据文件
const char OUTPUT_FEATURE_FILE[] = "output_features.txt"; // 输出特征文件
const int FIR_OUTPUT_FREQ = 250;       // FIR时钟频率（Hz）
const int PHYS_MAX_PERIOD = 1;      // 允许的最大生理周期（秒）
const int CIRCULAR_BUF_SIZE = 512;     // 循环缓存长度（必须是2^N）
const int NORMALIZED_POINTS = 200;     // 归一化点数

//-------- 数据加载函数 ----------
int load_input_data(const char* filename, std::vector<float>& data_buffer) {
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cerr << "错误：无法打开输入文件 " << filename << std::endl;
        return -1;
    }

    float val;
    while (in_file >> val) {          // 按行读取浮点数值
        data_buffer.push_back(val);
    }
    in_file.close();

    // 检查数据长度是否符合预期
    if (data_buffer.size() != CIRCULAR_BUF_SIZE) {
        std::cerr << "警告：输入数据长度(" << data_buffer.size()
                  << ") 与预期(" << CIRCULAR_BUF_SIZE << ") 不匹配" << std::endl;
    }
    return 0;
}

//-------- 主测试函数 -----------
int main() {
    // 初始化数据流
    hls::stream<float> fir_input_stream;
    hls::stream<float> feature_output_stream;

    // 加载输入波形数据
    std::vector<float> input_waveform;
    if (load_input_data(INPUT_DATA_FILE, input_waveform) != 0) {
        return 1;
    }

    //--------- 数据写入流程 ---------
    std::cout << "正在写入" << input_waveform.size() << "个采样点..." << std::endl;
    for (const auto& val : input_waveform) {
        fir_input_stream << val;          // 从数组写入HLS流
    }

    //--------- 执行设计 ---------
    std::cout << "开始执行特征提取..." << std::endl;
    feature_extractor_ip(fir_input_stream, feature_output_stream);

    //--------- 结果处理 ---------
    std::ofstream out_file(OUTPUT_FEATURE_FILE);
    if (!out_file.is_open()) {
        std::cerr << "错误：无法创建输出文件" << std::endl;
        return 1;
    }

    // 读取所有输出特征（假设每个周期输出四个特征）
    int feature_count = 0;
    while (!feature_output_stream.empty()) {
        float aip, slope, tdia, sip;
        feature_output_stream >> aip;     // 读取特征顺序必须与写入顺序一致
        feature_output_stream >> slope;
        feature_output_stream >> tdia;
        feature_output_stream >> sip;

        // 写入文件和控制台
        out_file << "Feature_Set:" << feature_count << "\n"
                 << "AIP: " << aip << "\n"
                 << "Slope: " << slope << "\n"
                 << "TDIA: " << tdia << "\n"
                 << "SIP: " << sip << "\n\n";

        std::cout << "特征集合 #" << feature_count++ << ":\n"
                  << "  AIP(拐点幅值): " << aip << "\n"
                  << "  Slope(斜率):   " << slope << "\n"
                  << "  TDIA(峰位置):  " << tdia << "\n"
                  << "  SIP(面积积分): " << sip << "\n"
                  << "------------------------" << std::endl;
    }

    out_file.close();
    std::cout << "\n测试完成！结果已保存至: " << OUTPUT_FEATURE_FILE << std::endl;
    return 0;
}
