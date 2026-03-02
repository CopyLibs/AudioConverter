import com.vanniktech.maven.publish.AndroidSingleVariantLibrary
import com.vanniktech.maven.publish.JavadocJar
import com.vanniktech.maven.publish.SourcesJar

plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.kotlin.android)
    id("com.vanniktech.maven.publish") version "0.36.0"
    id("signing")
}

android {
    namespace = "io.github.copylibs.audiolib"
    compileSdk = 36

    defaultConfig {
        minSdk = 27
    }

    externalNativeBuild {
        cmake {
            path("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

kotlin {
    jvmToolchain(JavaVersion.VERSION_17.toString().toInt())
}

dependencies {
}

mavenPublishing {
    configure(
        AndroidSingleVariantLibrary(
            javadocJar = JavadocJar.None(),
            sourcesJar = SourcesJar.Sources(),
            variant = "release",
        )
    )

    coordinates(
        groupId = "io.github.copylibs",
        artifactId = "audio-converter",
        version = "1.0.0.beta3"
    )

    pom {
        name = "AudioConverter"
        description = "Audio Converter For Android"
        url = "https://github.com/CopyLibs/AudioConverter"
        licenses {
            license {
                name = "The Apache License, Version 2.0"
                url = "http://www.apache.org/licenses/LICENSE-2.0.txt"
            }
        }
        developers {
            developer {
                name = "HdShare"
                url = "https://github.com/HdShare"
            }
        }
        scm {
            url = "https://github.com/CopyLibs/AudioConverter"
            connection = "scm:git:git://github.com/CopyLibs/AudioConverter.git"
            developerConnection = "scm:git:ssh://git@github.com/CopyLibs/AudioConverter.git"
        }
    }

    publishToMavenCentral()
    signAllPublications()
}
