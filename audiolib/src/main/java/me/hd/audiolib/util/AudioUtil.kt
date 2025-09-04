package me.hd.audiolib.util

import me.hd.audiolib.native.AudioNative
import java.io.File
import java.io.IOException

object AudioUtil {
    private var _tmpPath: String? = null
    private val tmpPath: String get() = requireNotNull(_tmpPath) { "AudioUtil must be init" }

    init {
        System.loadLibrary("audio")
    }

    @Throws(IOException::class)
    fun init(path: String) {
        _tmpPath = path
        val tmpDir = File(tmpPath)
        if (!tmpDir.canWrite()) throw IOException("init: 缓存目录无写入权限")
    }

    private fun getTmpFile(type: String): File {
        val fileName = "tmp_audio_${type}_${System.currentTimeMillis()}.$type"
        return File(tmpPath, fileName)
    }

    private fun checkFile(tag: String, file: File) {
        if (!file.exists() || file.length() == 0L) throw IOException("$tag: 文件不存在或为空")
    }

    fun mp3ToPcm(mp3File: File): File {
        checkFile("mp3ToPcm", mp3File)
        val pcmFile = getTmpFile("pcm")
        AudioNative.mp3ToPcm(mp3File.absolutePath, pcmFile.absolutePath)
        return pcmFile
    }

    fun pcmToSilk(pcmFile: File): File {
        checkFile("pcmToSilk", pcmFile)
        val silkFile = getTmpFile("silk")
        AudioNative.pcmToSilk(pcmFile.absolutePath, silkFile.absolutePath)
        return silkFile
    }

    fun mp3ToSilk(mp3File: File): File {
        checkFile("mp3ToSilk", mp3File)
        val pcmFile = getTmpFile("pcm")
        val sampleRate = AudioNative.mp3ToPcm(mp3File.absolutePath, pcmFile.absolutePath)
        val silkFile = getTmpFile("silk")
        AudioNative.pcmToSilk(pcmFile.absolutePath, silkFile.absolutePath, sampleRate)
        pcmFile.delete()
        return silkFile
    }

    fun silkToPcm(silkFile: File): File {
        checkFile("silkToPcm", silkFile)
        val pcmFile = getTmpFile("pcm")
        AudioNative.silkToPcm(silkFile.absolutePath, pcmFile.absolutePath)
        return pcmFile
    }

    fun pcmToMp3(pcmFile: File): File {
        checkFile("pcmToMp3", pcmFile)
        val mp3File = getTmpFile("mp3")
        AudioNative.pcmToMp3(pcmFile.absolutePath, mp3File.absolutePath)
        return mp3File
    }

    fun silkToMp3(silkFile: File): File {
        checkFile("silkToMp3", silkFile)
        val pcmFile = getTmpFile("pcm")
        AudioNative.silkToPcm(silkFile.absolutePath, pcmFile.absolutePath)
        val mp3File = getTmpFile("mp3")
        AudioNative.pcmToMp3(pcmFile.absolutePath, mp3File.absolutePath)
        pcmFile.delete()
        return mp3File
    }

    fun getSilkDuration(silkFile: File): Int {
        checkFile("getSilkDuration", silkFile)
        val pcmFile = getTmpFile("pcm")
        AudioNative.silkToPcm(silkFile.absolutePath, pcmFile.absolutePath)
        val duration = (pcmFile.length() / (2 * 24000) * 1000).toInt()
        pcmFile.delete()
        return duration.coerceAtLeast(1)
    }

    fun getSilkDuration(silkPath: String): Int {
        val silkFile = File(silkPath)
        return getSilkDuration(silkFile)
    }
}