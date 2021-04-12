#include "audio_pipeline.h"

#ifndef HTTPSTREAM_H
#define HTTPSTREAM_H



void httpstream_init(audio_pipeline_handle_t *pipeline);
void httpstream_settarget(audio_pipeline_handle_t *pipeline, char* target);
void httpstream_destroy(audio_pipeline_handle_t *pipeline);

#endif