//
// Created by Davy on 15-3-2021.
//

#include "mp3.h"

static int size = 5;

static MenuItem menuItems[] = {
    {"Play MP3", "Speel MP3", &play},
    {"Next song", "Volgend nummer", &next},
    {"Previous song", "Vorig nummer", &previous},
    {"Stop MP3", "Stop MP3", &stop},
    {"Return", "Terug", &returnFromMp3}};

void launchMP3Menu()
{
    setMenu(menuItems, size, "| MP3 Player |", "| MP3 Speler |");
    audiocontroller_setSource(3);
};

void play()
{
    ESP_LOGI("FUNCTION CALLED", "Play");
    audiocontroller_setTarget("0");
};

void next()
{
    audiocontroller_setTarget("1");
}

void previous()
{
    audiocontroller_setTarget("-1");
}

void stop()
{
    ESP_LOGI("FUNCTION CALLED", "Stop");
    audiocontroller_destroy();
};

void returnFromMp3()
{
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};
