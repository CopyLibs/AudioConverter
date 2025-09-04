#ifndef AUDIO_NATIVE_H
#define AUDIO_NATIVE_H

#include <jni.h>

class AudioNative {
public:
    static void init(JNIEnv *env);
};

#endif //AUDIO_NATIVE_H
