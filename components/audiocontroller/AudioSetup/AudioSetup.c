//
// Created by Davy on 16-3-2021.
//

#include "AudioSetup.h"
#include "internetradio.h"

static const char *TAG = "AudioSetup";

void setupAudio(esp_periph_set_handle_t *peripherals_pool){
    // Reduce logging levels, so our console doesnt get spammed with unnecessary information
    

    ESP_LOGD(TAG, "audio controller init");
    audiocontroller_init(peripherals_pool);
    ESP_LOGE(TAG, "DONE WITH SETUPAUDIO");
};