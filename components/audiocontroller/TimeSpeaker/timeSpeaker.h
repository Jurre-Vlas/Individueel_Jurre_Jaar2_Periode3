//
// Created by Davy on 19-3-2021.
//

#ifndef SMARTSPEAKER_TIMESPEAKER_H
#define SMARTSPEAKER_TIMESPEAKER_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
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
#include "../audioController.h"

void speakAudio();

#endif //SMARTSPEAKER_TIMESPEAKER_H
