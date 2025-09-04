# AudioConverter

![Maven Central Version](https://img.shields.io/maven-central/v/io.github.copylibs/audio-converter)

Audio Converter For Android

## 依赖

```kotlin
implementation("io.github.copylibs:audio-converter:$version")
```

## 用法

1. 初始化缓存目录
   ```kotlin
   AudioUtil.init(cacheDir.absolutePath)
   ```

2. 相关转换方法
   ```kotlin
   fun mp3ToPcm(mp3File: File): File
   fun pcmToSilk(pcmFile: File): File
   fun mp3ToSilk(mp3File: File): File
   
   fun silkToPcm(silkFile: File): File
   fun pcmToMp3(pcmFile: File): File
   fun silkToMp3(silkFile: File): File
   ```

## 致谢

- [lame](https://sourceforge.net/projects/lame/files/lame/)
- [silk-v3-decoder](https://github.com/kn007/silk-v3-decoder)
- [silk4j](https://github.com/mzdluo123/silk4j)