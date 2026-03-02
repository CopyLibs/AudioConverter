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
    // LAME requires: mp3buf >= 1.25 * num_samples + 7200 bytes.
    unsigned char output[static_cast<int>(BUFFER_SIZE * 1.25f) + 7200];

    int read = 0;
    int write = 0;
    int total = 0;

    do {
        read = static_cast<int>(fread(input, sizeof(short), BUFFER_SIZE, pcmFile));
        if (read > 0) {
            write = lame_encode_buffer(lame, input, input, read, output, static_cast<int>(sizeof(output)));
            if (write < 0) write = 0;
            total += write;
            if (write > 0) fwrite(output, 1, write, mp3File);
        } else {
            write = lame_encode_flush(lame, output, static_cast<int>(sizeof(output)));
            if (write < 0) write = 0;
            if (write > 0) fwrite(output, 1, write, mp3File);
        }
    } while (read > 0);

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
    mp3data_struct mp3data{};

    FILE *mp3File, *pcmFile;
    mp3File = fopen(mp3Path, "rb");
    pcmFile = fopen(pcmPath, "wb");
    if (mp3File == nullptr || pcmFile == nullptr) return 0;

    unsigned char id3Header[10];
    size_t id3Read = fread(id3Header, 1, sizeof(id3Header), mp3File);
    if (id3Read == sizeof(id3Header) && id3Header[0] == 'I' && id3Header[1] == 'D' && id3Header[2] == '3') {
        int tagSize = ((id3Header[6] & 0x7F) << 21) | ((id3Header[7] & 0x7F) << 14) | ((id3Header[8] & 0x7F) << 7) | (id3Header[9] & 0x7F);
        long skipBytes = static_cast<long>(10 + tagSize);
        fseek(mp3File, skipBytes, SEEK_SET);
    } else {
        fseek(mp3File, 0, SEEK_SET);
    }

    unsigned char input[BUFFER_SIZE];
    short output_l[BUFFER_SIZE * 20];
    short output_r[BUFFER_SIZE * 20];
    memset(output_l, 0, sizeof(output_l));
    memset(output_r, 0, sizeof(output_r));

    size_t read = 0;
    size_t total = 0;
    int sampleRate = 0;

    do {
        read = fread(input, 1, BUFFER_SIZE, mp3File);
        if (read > 0) {
            int decoded = hip_decode_headers(hip, input, read, output_l, output_r, &mp3data);
            if (decoded > 0) {
                size_t writeCount = static_cast<size_t>(decoded);
                total += writeCount;
                fwrite(output_l, sizeof(short), writeCount, pcmFile);
                sampleRate = mp3data.samplerate;
            }
        } else if (total == 0) {
            memset(input, 0, BUFFER_SIZE);
            int decoded = hip_decode_headers(hip, input, 10, output_l, output_r, &mp3data);
            if (decoded > 0) {
                size_t writeCount = static_cast<size_t>(decoded);
                fwrite(output_l, sizeof(short), writeCount, pcmFile);
                total += writeCount;
                sampleRate = mp3data.samplerate;
            }
        }
    } while (read > 0);

    fclose(pcmFile);
    fclose(mp3File);

    return sampleRate;
}

void LameCoder::Mp3ToPcmClose() {
    hip_decode_exit(hip);
}
