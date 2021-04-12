#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "http_stream.h"
#include "i2s_stream.h"
#include "mp3_decoder.h"

#include "esp_peripherals.h"
#include "periph_wifi.h"
#include "board.h"
#include "esp_idf_version.h"
#include "esp_netif.h"
#include "Sources/httpStream.h"
#include "Sources/whitenoise.h"
#include "Sources/mp3.h"
#include "Sources/rawStream.h"
#include "Sources/timesource.h"

void audiocontroller_init(esp_periph_set_handle_t *setPtr);
void audiocontroller_setTarget(void* callback);
void audiocontroller_setSource(unsigned int id);
void audiocontroller_destroy();

typedef struct 
{
    char shortName[10];
    void (*init)(audio_pipeline_handle_t *pipeline);
    void (*settarget)(audio_pipeline_handle_t *pipeline, char* target);
    void (*destroy)(audio_pipeline_handle_t *pipeline);
} inputSource;

#endif