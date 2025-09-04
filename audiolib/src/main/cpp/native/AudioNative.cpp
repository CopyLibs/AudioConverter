#include "AudioNative.h"
#include "audio/SilkCoder.h"
#include "audio/LameCoder.h"

void silkToPcmConvert(
        JNIEnv *env, jobject clazz,
        jstring silkPath, jstring pcmPath, jboolean debug,
        jint fs_Hz, jint loss
) {
    const char *nativeSilkPath = env->GetStringUTFChars(silkPath, nullptr);
    const char *nativePcmPath = env->GetStringUTFChars(pcmPath, nullptr);
    SilkCoder::SilkToPcmConvert(
            nativeSilkPath, nativePcmPath, debug,
            fs_Hz, loss
    );
    env->ReleaseStringUTFChars(silkPath, nativeSilkPath);
    env->ReleaseStringUTFChars(pcmPath, nativePcmPath);
}

void pcmToSilkConvert(
        JNIEnv *env, jobject clazz,
        jstring pcmPath, jstring silkPath, jboolean tencent, jboolean debug,
        jint fs_Hz, jint maxInternalSampleRate, jint packetSizeMs, jint packetLossPercentage,
        jint useInBandFEC, jint useDTX, jint complexity, jint bitRate
) {
    const char *nativePcmPath = env->GetStringUTFChars(pcmPath, nullptr);
    const char *nativeSilkPath = env->GetStringUTFChars(silkPath, nullptr);
    SilkCoder::PcmToSilkConvert(
            nativePcmPath, nativeSilkPath, tencent, debug,
            fs_Hz, maxInternalSampleRate, packetSizeMs, packetLossPercentage,
            useInBandFEC, useDTX, complexity, bitRate
    );
    env->ReleaseStringUTFChars(pcmPath, nativePcmPath);
    env->ReleaseStringUTFChars(silkPath, nativeSilkPath);
}

void pcmToMp3Init(
        JNIEnv *env, jobject clazz,
        jint inputSampleRate, jfloat inputScale, jint inputChannelCount,
        jint outputSampleRate, jint outputBitrate,
        jint encodingQuality, jint vbrQuality, jint abrMeanBitrate,
        jint vbrMode, jint mode,
        jint lowPassFrequency, jint highPassFrequency
) {
    LameCoder::PcmToMp3Init(
            inputSampleRate, inputScale, inputChannelCount,
            outputSampleRate, outputBitrate,
            encodingQuality, vbrQuality, abrMeanBitrate,
            vbrMode, mode,
            lowPassFrequency, highPassFrequency
    );
}

void pcmToMp3Convert(
        JNIEnv *env, jobject clazz,
        jstring pcmPath, jstring mp3Path
) {
    const char *nativePcmPath = env->GetStringUTFChars(pcmPath, nullptr);
    const char *nativeMp3Path = env->GetStringUTFChars(mp3Path, nullptr);
    LameCoder::PcmToMp3Convert(
            nativePcmPath, nativeMp3Path
    );
    env->ReleaseStringUTFChars(pcmPath, nativePcmPath);
    env->ReleaseStringUTFChars(mp3Path, nativeMp3Path);
}

void pcmToMp3Close(
        JNIEnv *env, jobject clazz
) {
    LameCoder::PcmToMp3Close();
}

void mp3ToPcmInit(
        JNIEnv *env, jobject clazz
) {
    LameCoder::Mp3ToPcmInit();
}

int mp3ToPcmConvert(
        JNIEnv *env, jobject clazz,
        jstring mp3Path, jstring pcmPath
) {
    const char *nativeMp3Path = env->GetStringUTFChars(mp3Path, nullptr);
    const char *nativePcmPath = env->GetStringUTFChars(pcmPath, nullptr);
    int sampleRate = LameCoder::Mp3ToPcmConvert(
            nativeMp3Path, nativePcmPath
    );
    env->ReleaseStringUTFChars(mp3Path, nativeMp3Path);
    env->ReleaseStringUTFChars(pcmPath, nativePcmPath);
    return sampleRate;
}

void mp3ToPcmClose(
        JNIEnv *env, jobject clazz
) {
    LameCoder::Mp3ToPcmClose();
}

void AudioNative::init(JNIEnv *env) {
    jclass clazz = env->FindClass("me/hd/audiolib/native/AudioNative");
    JNINativeMethod methods[] = {
            {"silkToPcmConvert", "(Ljava/lang/String;Ljava/lang/String;ZII)V",        (void *) silkToPcmConvert},
            {"pcmToSilkConvert", "(Ljava/lang/String;Ljava/lang/String;ZZIIIIIIII)V", (void *) pcmToSilkConvert},
            {"pcmToMp3Init",     "(IFIIIIIIIIII)V",                                   (void *) pcmToMp3Init},
            {"pcmToMp3Convert",  "(Ljava/lang/String;Ljava/lang/String;)V",           (void *) pcmToMp3Convert},
            {"pcmToMp3Close",    "()V",                                               (void *) pcmToMp3Close},
            {"mp3ToPcmInit",     "()V",                                               (void *) mp3ToPcmInit},
            {"mp3ToPcmConvert",  "(Ljava/lang/String;Ljava/lang/String;)I",           (void *) mp3ToPcmConvert},
            {"mp3ToPcmClose",    "()V",                                               (void *) mp3ToPcmClose},
    };
    const int methodCount = sizeof(methods) / sizeof(methods[0]);
    if (env->RegisterNatives(clazz, methods, methodCount) < 0) {
        LOGE("AudioNative registerNatives failed");
    }
    env->DeleteLocalRef(clazz);
}
