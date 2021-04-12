//
// Created by Davy on 15-3-2021.
//

#include "mp3.h"

static int size = 3;

static MenuItem menuItems[] = {
        {"Play MP3", "Speel MP3", &Play},
        {"Stop MP3", "Stop MP3", &Stop},
        {"Return", "Terug", &returnFromMp3}};


void launchMP3Menu(){
    setMenu(menuItems, size, "| MP3 Player |", "| MP3 Speler |");
};

void Play(){
    ESP_LOGI("FUNCTION CALLED", "Play");
};

void Stop(){
    ESP_LOGI("FUNCTION CALLED", "Stop");
};

void returnFromMp3(){
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};
