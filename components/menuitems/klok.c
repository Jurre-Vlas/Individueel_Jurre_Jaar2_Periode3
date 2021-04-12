
#include "klok.h"

static int size = 2;

static MenuItem menuItems[] = {
        {"Dutch Time", "Nederlandse Tijd",  &DutchTime},
        {"Return", "Terug", &returnFromTalkingClock}};


void launchTalkingClockMenu() {
    setMenu(menuItems, size, "| Time |", "| Klok |");
}

void DutchTime(){
    ESP_LOGI("Starting a talking clock song now...", "");
    getZone("TZ", "CET-1CEST,M3.5.0,M10.5.0/3");
    getTime();
    play_time();
};

void newZeland(){
    ESP_LOGI("Starting a talking clock song now...", "");
    getZone("TZ", "NZST-12NZDT-13,M10.1.0/02:00:00,M3.3.0/03:00:00");
    getTime();
    play_time();
};


void returnFromTalkingClock(){
    ESP_LOGI("RETURN", "");
    launchHomeMenu();
};
