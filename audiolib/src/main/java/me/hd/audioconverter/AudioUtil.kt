package me.hd.audioconverter

object AudioUtil {
    init {
        System.loadLibrary("audio")
    }

    external fun stringFromJNI(): String
}