package me.hd.audioconverter.native

object AudioNative {
    external fun silkToPcmConvert(
        silkPath: String,
        pcmPath: String,
        debug: Boolean = false,
        fs_Hz: Int = 24000,
        loss: Int = 0
    )

    external fun pcmToSilkConvert(
        pcmPath: String,
        silkPath: String,
        tencent: Boolean = true,
        debug: Boolean = false,
        fs_Hz: Int = 24000,
        maxInternalSampleRate: Int = 24000,
        packetSizeMs: Int = 20,
        packetLossPercentage: Int = 0,
        useInBandFEC: Int = 0,
        useDTX: Int = 0,
        complexity: Int = 2,
        bitRate: Int = 24000
    )

    external fun pcmToMp3Init(
        inputSampleRate: Int = 24000,
        inputScale: Float = 1f,
        outputChannelCount: Int = 1,
        outputSampleRate: Int = 24000,
        outputBitrate: Int = 48,
        encodingQuality: Int = 8,
        vbrQuality: Int = 5,
        abrMeanBitrate: Int = 128,
        vbrMode: Int = 0,
        mode: Int = 3,
        lowPassFrequency: Int = 0,
        highPassFrequency: Int = 0
    )

    external fun pcmToMp3Convert(
        pcmPath: String,
        mp3Path: String
    )

    external fun pcmToMp3Close()

    external fun mp3ToPcmInit()

    external fun mp3ToPcmConvert(
        mp3Path: String,
        pcmPath: String
    ): Int

    external fun mp3ToPcmClose()

    fun silkToPcm(silkPath: String, pcmPath: String) {
        silkToPcmConvert(silkPath, pcmPath)
    }

    fun pcmToSilk(pcmPath: String, silkPath: String, sampleRate: Int = 24000) {
        pcmToSilkConvert(pcmPath, silkPath, fs_Hz = sampleRate)
    }

    fun pcmToMp3(pcmPath: String, mp3Path: String) {
        pcmToMp3Init()
        pcmToMp3Convert(pcmPath, mp3Path)
        pcmToMp3Close()
    }

    fun mp3ToPcm(mp3Path: String, pcmPath: String): Int {
        mp3ToPcmInit()
        val sampleRate = mp3ToPcmConvert(mp3Path, pcmPath)
        mp3ToPcmClose()
        return sampleRate
    }
}