#include "audio_pipeline.h"

#ifndef WHITENOISE_H
#define WHITENOISE_H

void whitenoise_init(audio_pipeline_handle_t *pipeline);
void whitenoise_settarget(audio_pipeline_handle_t *pipeline, char *target);
void whitenoise_destroy(audio_pipeline_handle_t *pipeline);

#endif