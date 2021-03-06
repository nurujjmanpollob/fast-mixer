#ifndef MODULE_NAME
#define MODULE_NAME  "native-lib"
#endif

#include <jni.h>
#include <string>
#include "AudioEngine.h"
#include "logging_macros.h"

const char *TAG = "native-lib: %s";
static AudioEngine *audioEngine = nullptr;

extern "C" {
    JNIEXPORT jboolean JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_create(JNIEnv *env, jclass, jstring appDirStr, jstring recordingSessionIdStr) {
        LOGD(TAG, "create(): ");
        if (audioEngine == nullptr) {
            char* appDir = const_cast<char *>(env->GetStringUTFChars(appDirStr, NULL));
            char* recordingSessionId = const_cast<char *>(env->GetStringUTFChars(
                    recordingSessionIdStr, NULL));
            audioEngine = new AudioEngine(appDir, recordingSessionId);
        }
        return (audioEngine != nullptr);
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_delete(JNIEnv *env, jclass) {
        LOGD(TAG, "delete(): ");
        delete audioEngine;
        audioEngine = nullptr;
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_startRecording(JNIEnv *env, jclass) {
        LOGD(TAG, "startRecording(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->startRecording();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_stopRecording(JNIEnv *env, jclass) {
        LOGD(TAG, "stopRecording(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->stopRecording();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_pauseRecording(JNIEnv *env, jclass) {
        LOGD(TAG, "pauseRecording(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->pauseRecording();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_startPlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "startPlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->startPlayback();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_stopPlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "stopPlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->stopPlayback();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_pausePlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "pausePlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->pausePlayback();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_startLivePlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "startLivePlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->startLivePlayback();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_stopLivePlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "stopLivePlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->stopLivePlayback();
    }

    JNIEXPORT void JNICALL
    Java_com_bluehub_fastmixer_common_audio_AudioEngine_pauseLivePlayback(JNIEnv *env, jclass) {
        LOGD(TAG, "pauseLivePlayback(): ");
        if (audioEngine == nullptr) {
            LOGE("audioEngine is null, you must call create() method before calling this method");
            return;
        }
        audioEngine->pauseLivePlayback();
    }


}