#ifndef LAME_CODER_H
#define LAME_CODER_H

#include "lame.h"

#define BUFFER_SIZE 8192

class LameCoder {
private:
    static lame_t lame;
    static hip_t hip;

public:
    static void PcmToMp3Init(
            int inputSampleRate,
            float inputScale,
            int outputChannelCount,
            int outputSampleRate,
            int outputBitrate,
            int encodingQuality,
            int vbrQuality,
            int abrMeanBitrate,
            int vbrMode,
            int mode,
            int lowPassFrequency,
            int highPassFrequency
    );

    static void PcmToMp3Convert(
            const char *pcmPath,
            const char *mp3Path
    );

    static void PcmToMp3Close();

    static void Mp3ToPcmInit();

    static int Mp3ToPcmConvert(
            const char *mp3Path,
            const char *pcmPath
    );

    static void Mp3ToPcmClose();
};

#endif //LAME_CODER_H
