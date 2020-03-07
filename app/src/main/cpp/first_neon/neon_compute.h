//
// Created by Administrator on 2020/3/7.
//

#ifndef NEON_DEMO_NEON_COMPUTE_H
#define NEON_DEMO_NEON_COMPUTE_H

#include <android/log.h>
#include <arm_neon.h>
#include <sys/time.h>


#define LOG_TAG "NEON_DEMO"
#ifdef LOG_TAG
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型
#endif

void test();

void add_float_c(float* dst, float* src1, float* src2, int count);

void add_float_neon1(float* dst, float* src1, float* src2, int count);

void add_float_neon3_aarch32(float* dst, float* src1, float* src2, int count);

//void add_float_neon3_aarch64(float* dst, float* src1, float* src2, int count);

#endif //NEON_DEMO_NEON_COMPUTE_H
