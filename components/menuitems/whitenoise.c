//
// Created by Davy on 15-3-2021.
//

#include "whitenoise.h"

static int size = 3;

static MenuItem menuItems[] = {
        {"Play", "Afspelen", &PlayWN},
        {"Stop", "Stoppen", &StopWN},
        {"Return", "Terug", &returnFromWN}};


void launchWhiteNoiseMenu() {
    setMenu(menuItems, size, "| White Noise |", "| Wit geluid |");
}

void PlayWN(){
    ESP_LOGI("PLAYING WHITE NOISE", "");
    audiocontroller_setSource(1);
    audiocontroller_setTarget("");
};

void StopWN(){
    ESP_LOGI("STOPPING WHITE NOISE", "");
    audiocontroller_destroy();
};

void returnFromWN(){
    ESP_LOGI("RETURN", "");
    launchHomeMenu();
};
