//
// Created by Mick on 19/03/2021.
//

#ifndef INC_2021_TI23_A2_AUDIORECOGNITION_H
#define INC_2021_TI23_A2_AUDIORECOGNITION_H

#define GOERTZEL_SAMPLE_RATE_HZ 8000
#define GOERTZEL_FRAME_LENGTH_MS 100
#define GOERTZEL_BUFFER_LENGTH (GOERTZEL_FRAME_LENGTH_MS * GOERTZEL_SAMPLE_RATE_HZ / 1000)
#define AUDIO_SAMPLE_RATE 48000
#define GOERTZEL_N_DETECTION 3

#include "audioController.h"
#include "goertzel.h"
#include "esp_log.h"

static const int GOERTZEL_DETECT_FREQUENCIES[GOERTZEL_N_DETECTION] = {
        870,880,890
};
void audioRecognition_init();
void recognizeAudio(int16_t *raw_buff);

#endif //INC_2021_TI23_A2_AUDIORECOGNITION_H
