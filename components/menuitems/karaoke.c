//
// Created by Davy on 15-3-2021.
//

#include "karaoke.h"

static int size = 2;

static MenuItem menuItems[] = {
        {"Start karaoke", "Begin karaoke",  &StartKaraoke},
        {"Return", "Terug", &returnFromKaraoke}};


void launchKaraokeMenu() {
    setMenu(menuItems, size, "| Karaoke |", "| Meezingen! |");
}

void StartKaraoke(){
    ESP_LOGI("Starting a karaoke song now...", "");
};

void returnFromKaraoke(){
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};
