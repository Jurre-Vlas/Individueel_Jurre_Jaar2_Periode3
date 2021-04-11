#include "audio_pipeline.h"

#ifndef TIMESOURCE_H
#define TIMESOURCE_H

void timesource_init(audio_pipeline_handle_t *pipeline);
void timesource_settarget(audio_pipeline_handle_t *pipeline, char *target);
void timesource_destroy(audio_pipeline_handle_t *pipeline);

#endif