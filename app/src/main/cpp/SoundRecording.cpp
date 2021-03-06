//
// Created by asalehin on 7/11/20.
//

#include <cstdint>
#include <cstdio>
#include <string>
#include <future>
#include "SoundRecording.h"
#include "logging_macros.h"
#include "Utils.h"

void SoundRecording::write_runnable(const int16_t *sourceData, int32_t numSamples, SoundRecording* soundRecording) {
    if (soundRecording->isRecordingFpOpen) {
        auto *buffer = new int16_t[numSamples]{0};

        for (int i = 0; i < numSamples; i++) {
            buffer[i] = soundRecording->gain_factor * sourceData[i];
        }

        fwrite(buffer, sizeof(*buffer), numSamples, soundRecording->recordingFp);
        fflush(soundRecording->recordingFp);

        soundRecording->mTotalSamples += numSamples;
    }
}

void SoundRecording::read_live_playback_runnable(int16_t *targetData, int32_t numSamples, SoundRecording* soundRecording) {
    LOGD(soundRecording->TAG, "readLivePlayback(): ");
    LOGD(soundRecording->TAG, std::to_string(numSamples).c_str());

    int32_t framesRead = 0;
    if (soundRecording->isLiveFpOpen) {
        framesRead = fread(targetData, sizeof(int16_t), numSamples, soundRecording->livePlaybackFp);
        soundRecording->mTotalReadLivePlayback += framesRead;
    }
}

void SoundRecording::read_playback_runnable(int16_t *targetData, int32_t numSamples, SoundRecording* soundRecording) {
    LOGD(soundRecording->TAG, "readPlayback(): ");
    LOGD(soundRecording->TAG, std::to_string(numSamples).c_str());

    int32_t framesRead = 0;
    if (soundRecording->isPlaybackFpOpen) {
        framesRead = fread(targetData, sizeof(int16_t), numSamples, soundRecording->playbackFp);
        soundRecording->mTotalReadPlayback += framesRead;
    }
}

int32_t SoundRecording::write(const int16_t *sourceData, int32_t numSamples) {
    write_runnable(sourceData, numSamples, this);
    return numSamples;
}

void SoundRecording::read_live_playback(int16_t *targetData, int32_t numSamples) {
    LOGD(TAG, "read(): ");
    LOGD(TAG, std::to_string(numSamples).c_str());
    // Live playback in main thread to prevent occasional lag that is being happened
    read_live_playback_runnable(targetData, numSamples, this);
}

void SoundRecording::read_playback(int16_t *targetData, int32_t numSamples) {
    LOGD(TAG, "read(): ");
    LOGD(TAG, std::to_string(numSamples).c_str());
    // Live playback in main thread to prevent occasional lag that is being happened
    read_playback_runnable(targetData, numSamples, this);
}

void SoundRecording::openRecordingFp() {
    if (!isRecordingFpOpen) {
        recordingFp = fopen(mRecordingFilePath.c_str(), "ab");
        isRecordingFpOpen = true;
    }
}

void SoundRecording::closeRecordingFp() {
    if (isRecordingFpOpen) {
        fclose(recordingFp);
        isRecordingFpOpen = false;
    }
}

void SoundRecording::openLivePlaybackFp() {
    if (!isLiveFpOpen) {
        livePlaybackFp = fopen(mRecordingFilePath.c_str(), "rb");
        isLiveFpOpen = true;
        fseek(livePlaybackFp, mTotalReadLivePlayback * sizeof(int16_t), SEEK_SET);
    }
}

void SoundRecording::closeLivePlaybackFp() {
    if (isLiveFpOpen) {
        fclose(livePlaybackFp);
        isLiveFpOpen = false;
    }
}

void SoundRecording::openPlaybackFp() {
    if (!isPlaybackFpOpen) {
        playbackFp = fopen(mRecordingFilePath.c_str(), "rb");
        isPlaybackFpOpen = true;
        fseek(playbackFp, mTotalReadPlayback * sizeof(int16_t), SEEK_SET);
    }
}

void SoundRecording::closePlaybackFp() {
    if (isPlaybackFpOpen) {
        fclose(playbackFp);
        isPlaybackFpOpen = false;
    }
}