#include "audio_pipeline.h"

#ifndef MP3_H
#define MP3_H

void mp3_init(audio_pipeline_handle_t *pipeline);
void mp3_settarget(audio_pipeline_handle_t *pipeline, char *target);
void mp3_destroy(audio_pipeline_handle_t *pipeline);

#endif