#ifndef SILK_CODER_H
#define SILK_CODER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include "utils/log.h"
#include "SKP_Silk_SDK_API.h"
#include "SKP_Silk_SigProc_FIX.h"

#define MAX_BYTES_PER_FRAME     1024
#define MAX_INPUT_FRAMES        5
#define MAX_FRAME_LENGTH        480
#define FRAME_LENGTH_MS         20
#define MAX_API_FS_KHZ          48
#define MAX_LBRR_DELAY          2

/* Seed for the random number generator, which is used for simulating packet loss */
static SKP_int32 rand_seed = 1;

class SilkCoder {
public:
    static void SilkToPcmConvert(
            const char *silkPath,
            const char *pcmPath,
            bool debug,
            int fs_Hz,
            int loss
    );

    static void PcmToSilkConvert(
            const char *pcmPath,
            const char *silkPath,
            bool tencent,
            bool debug,
            int fs_Hz,
            int maxInternalSampleRate,
            int packetSizeMs,
            int packetLossPercentage,
            int useInBandFEC,
            int useDTX,
            int complexity,
            int bitRate
    );
};

#endif //SILK_CODER_H
