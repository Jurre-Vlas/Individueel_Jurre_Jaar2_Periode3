//
// Created by Mick on 19/03/2021.
//

#ifndef INC_2021_TI23_A2_RAWSTREAM_H
#define INC_2021_TI23_A2_RAWSTREAM_H

#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "raw_stream.h"
#include "i2s_stream.h"
#include "filter_resample.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "audioRecognition.h"
#include "goertzel.h"

#define GOERTZEL_BUFFER_LENGTH (GOERTZEL_FRAME_LENGTH_MS * GOERTZEL_SAMPLE_RATE_HZ / 1000)
#define GOERTZEL_SAMPLE_RATE_HZ 8000
#define GOERTZEL_FRAME_LENGTH_MS 100
#define AUDIO_SAMPLE_RATE 48000

typedef void (*goertzel_data_callback)(int16_t*);

void rawStream_init(audio_pipeline_handle_t *pipeline);
void rawStream_settarget(audio_pipeline_handle_t *pipeline, char* target);
void rawStream_destroy(audio_pipeline_handle_t *pipeline);

#endif //INC_2021_TI23_A2_RAWSTREAM_H
