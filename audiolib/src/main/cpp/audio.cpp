#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_me_hd_audioconverter_AudioUtil_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}