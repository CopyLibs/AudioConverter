package io.github.copylibs.audiolib

import android.app.Activity
import android.os.Bundle
import io.github.copylibs.audiolib.databinding.ActivityMainBinding
import io.github.copylibs.audiolib.util.AudioUtil
import java.io.File

class MainActivity : Activity() {
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        AudioUtil.init(cacheDir.absolutePath)
        initView()
    }

    private fun initView() {
        binding.edtInputPath.setText(filesDir.absolutePath)
        binding.edtOutputPath.setText(filesDir.absolutePath)
        binding.btnMp3ToPcm.setOnClickListener {
            val mp3Path = binding.edtInputPath.text.toString()
            val pcmPath = binding.edtOutputPath.text.toString()
            AudioUtil.mp3ToPcm(File(mp3Path)).copyTo(File(pcmPath), true)
        }
        binding.btnPcmToMp3.setOnClickListener {
            val pcmPath = binding.edtInputPath.text.toString()
            val mp3Path = binding.edtOutputPath.text.toString()
            AudioUtil.pcmToMp3(File(pcmPath)).copyTo(File(mp3Path), true)
        }
        binding.btnMp3ToSilk.setOnClickListener {
            val mp3Path = binding.edtInputPath.text.toString()
            val silkPath = binding.edtOutputPath.text.toString()
            AudioUtil.mp3ToSilk(File(mp3Path)).copyTo(File(silkPath), true)
        }
        binding.btnSilkToMp3.setOnClickListener {
            val silkPath = binding.edtInputPath.text.toString()
            val mp3Path = binding.edtOutputPath.text.toString()
            AudioUtil.silkToMp3(File(silkPath)).copyTo(File(mp3Path), true)
        }
    }
}
