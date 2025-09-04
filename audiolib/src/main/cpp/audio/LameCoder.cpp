#include "LameCoder.h"

lame_t LameCoder::lame = nullptr;

void LameCoder::PcmToMp3Init(
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
) {
    lame = lame_init();
    lame_set_in_samplerate(lame, inputSampleRate);
    lame_set_scale(lame, inputScale);
    lame_set_num_channels(lame, outputChannelCount);
    lame_set_out_samplerate(lame, outputSampleRate);
    lame_set_brate(lame, outputBitrate);
    lame_set_quality(lame, encodingQuality);
    lame_set_VBR_q(lame, vbrQuality);
    lame_set_VBR_mean_bitrate_kbps(lame, abrMeanBitrate);
    switch (vbrMode) {
        case 0:
            lame_set_VBR(lame, vbr_off);
            break;
        case 2:
            lame_set_VBR(lame, vbr_rh);
            break;
        case 3:
            lame_set_VBR(lame, vbr_abr);
            break;
        case 4:
            lame_set_VBR(lame, vbr_mtrh);
            break;
        case 5:
            lame_set_VBR(lame, vbr_default);
            break;
        default:
            lame_set_VBR(lame, vbr_off);
            break;
    }
    switch (mode) {
        case 0:
            lame_set_mode(lame, STEREO);
            break;
        case 1:
            lame_set_mode(lame, JOINT_STEREO);
            break;
        case 3:
            lame_set_mode(lame, MONO);
            break;
        case 4:
            lame_set_mode(lame, NOT_SET);
            break;
        default:
            lame_set_mode(lame, NOT_SET);
            break;
    }
    lame_set_lowpassfreq(lame, lowPassFrequency);
    lame_set_highpassfreq(lame, highPassFrequency);
    lame_init_params(lame);
}

void LameCoder::PcmToMp3Convert(const char *pcmPath, const char *mp3Path) {
    FILE *pcmFile, *mp3File;
    pcmFile = fopen(pcmPath, "rb");
    mp3File = fopen(mp3Path, "wb");
    if (pcmFile == nullptr || mp3File == nullptr) return;

    short input[BUFFER_SIZE];
    unsigned char output[BUFFER_SIZE];

    int read = 0;
    int write = 0;
    int total = 0;

    read = static_cast<int>(fread(input, 1, sizeof(short), pcmFile) / sizeof(short));
    while (read) {
        write = lame_encode_buffer(lame, input, input, read, output, BUFFER_SIZE);
        total += write;
        fwrite(output, write, 1, mp3File);
        read = static_cast<int>(fread(input, 1, sizeof(short), pcmFile) / sizeof(short));
    }

    write = lame_encode_flush(lame, output, BUFFER_SIZE);
    fwrite(output, write, 1, mp3File);

    fclose(mp3File);
    fclose(pcmFile);
}

void LameCoder::PcmToMp3Close() {
    lame_close(lame);
}

hip_t LameCoder::hip = nullptr;

void LameCoder::Mp3ToPcmInit() {
    hip = hip_decode_init();
}

int LameCoder::Mp3ToPcmConvert(const char *mp3Path, const char *pcmPath) {
    mp3data_struct mp3data;

    FILE *mp3File, *pcmFile;
    mp3File = fopen(mp3Path, "rb");
    pcmFile = fopen(pcmPath, "wb");
    if (mp3File == nullptr || pcmFile == nullptr) return 0;

    unsigned char input[BUFFER_SIZE];
    short output_l[BUFFER_SIZE * 20];
    short output_r[BUFFER_SIZE * 20];
    memset(output_l, 0, BUFFER_SIZE * 20);
    memset(output_r, 0, BUFFER_SIZE * 20);

    size_t read = 0;
    size_t write = 0;
    size_t total = 0;

    read = fread(input, 1, BUFFER_SIZE, mp3File);
    while (read) {
        write = hip_decode_headers(hip, input, read, output_l, output_r, &mp3data);
        total += write;
        fwrite(output_l, write, sizeof(short), pcmFile);
        read = fread(input, 1, BUFFER_SIZE, mp3File);
    }
    if (total == 0) {
        memset(input, 0, BUFFER_SIZE);
        read = 10;
        write = hip_decode_headers(hip, input, read, output_l, output_r, &mp3data);
        fwrite(output_l, write, sizeof(short), pcmFile);
    }

    fclose(pcmFile);
    fclose(mp3File);

    return mp3data.samplerate;
}

void LameCoder::Mp3ToPcmClose() {
    hip_decode_exit(hip);
}
