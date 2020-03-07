//
// Created by Administrator on 2020/3/7.
//
#include "neon_compute.h"

#define  SIZE 2400000

static inline uint64_t getTimeInUs() {
    uint64_t time;
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    time = static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;

    return time;
}

void test()
{
LOGD("test NEON float array add.");
float* result1 = new float[SIZE];
float* result2 = new float[SIZE];
float* result3 = new float[SIZE];


float* src1 = new float[SIZE];
float* src2 = new float[SIZE];
for(int i = 0; i < SIZE; i++ ) {
    src1[i] = 1.0;
    src2[i] = 2.0;
}

int64_t t1 = getTimeInUs();
add_float_c(result1, src1, src2, SIZE);
int64_t t2 = getTimeInUs();


add_float_neon1(result2, src1, src2, SIZE);
int64_t t3 = getTimeInUs();

LOGD("test NEON before into neon assembly.");
add_float_neon3_aarch32(result3, src1, src2, SIZE);
LOGD("test NEON after into neon assembly.");
int64_t t4 = getTimeInUs();

LOGD("test NEON add float array in c, time: %d us", (t2 - t1));
LOGD("test NEON add float array in NEON, time：%d us", (t3 - t2));
LOGD("test NEON add float array in inline assembly, time: %d", (t4 - t3));

for(int i = 0; i < SIZE; i++) {
    float comp1 = result1[i] - result2[i];
    float comp2 = result3[i] - result1[i];
    if(comp1 != 0.0 || comp2 != 0) {
        LOGD("test NEON result error, result1: %f, result2: %f", result1[i], result2[i]);
        LOGD("test NEON result error, result1: %f, result3: %f", result1[i], result3[i]);
        break;
    }
}


}


//add for float array. assumed that count is multiple of 4

void add_float_c(float* dst, float* src1, float* src2, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        dst[i] = src1[i] + src2[i];
    }
}

void add_float_neon1(float* dst, float* src1, float* src2, int count)

{
    int i;
    for (i = 0; i < count; i += 4)
    {
        float32x4_t in1, in2, out;
        in1 = vld1q_f32(src1);
        src1 += 4;
        in2 = vld1q_f32(src2);
        src2 += 4;
        out = vaddq_f32(in1, in2);
        vst1q_f32(dst, out);
        dst += 4;

        // The following is only an example describing how to use AArch64 specific NEON
        // instructions.

#if defined (__aarch64__)
        float32_t tmp = vaddvq_f32(in1);
        //LOGD("test NEON use aarch64.");
#endif

    }
    // LOGD("test NEON, i: %d", i);
}

// Armv7-A/AArch32
void add_float_neon3_aarch32(float* dst, float* src1, float* src2, int count)
{
    LOGD("test NEON into neon inline assembly.");
    asm volatile (
    "1: \n"
    "vld1.32 {q0}, [%[src1]]! \n"
    "vld1.32 {q1}, [%[src2]]! \n"
    "vadd.f32 q0, q0, q1 \n"
    "subs %[count], %[count], #4 \n"
    "vst1.32 {q0}, [%[dst]]! \n"
    "bgt 1b \n"
    : [dst] "+r" (dst)
    : [src1] "r" (src1), [src2] "r" (src2), [count] "r" (count)
    : "memory", "q0", "q1"
    );
}


/*
// AArch64
void add_float_neon3_aarch64(float* dst, float* src1, float* src2, int count)
{
    asm volatile (
    "1: \n"
    "ld1 {v0.4s}, [%[src1]], #16 \n"
    "ld1 {v1.4s}, [%[src2]], #16 \n"
    "fadd v0.4s, v0.4s, v1.4s \n"
    "subs %[count], %[count], #4 \n"
    "st1 {v0.4s}, [%[dst]], #16 \n"
    "bgt 1b \n"
    : [dst] "+r" (dst)
    : [src1] "r" (src1), [src2] "r" (src2), [count] "r" (count)
    : "memory", "v0", "v1"
    );
}
 */

