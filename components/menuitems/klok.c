//
// Created by Davy on 15-3-2021.
//

#include "klok.h"

static int size = 2;

static MenuItem menuItems[] = {
        {"Say time", "Zeg tijd",  &StartTalkingClock},
        {"Return", "Terug", &returnFromTalkingClock}};


void launchTalkingClockMenu() {
    setMenu(menuItems, size, "| Talking Clock |", "| Pratende Klok |");
}

void StartTalkingClock(){
    ESP_LOGI("Starting a talking clock song now...", "");
    play_time();
};

void returnFromTalkingClock(){
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};
