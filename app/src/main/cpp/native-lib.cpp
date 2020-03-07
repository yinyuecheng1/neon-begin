#include <jni.h>
#include <string>
#include "first_neon/neon_compute.h"

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jstring JNICALL
Java_com_example_neon_1demo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    // test neon
    test();
    LOGD("test success.");
    std::string hello = "END TEST!!!";
    return env->NewStringUTF(hello.c_str());
}

#ifdef __cplusplus
}
#endif