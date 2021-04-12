
#include "klok.h"

#include <stdio.h>
#include <sys/time.h>
#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"
#include "time.h"

static int size = 3;

static MenuItem menuItems[] = {
        {"Dutch Time", "Nederlandse Tijd",  &dutchTime},
        {"NewZeland Time", "Nieuw-Zeeland Tijd",  &newZeland},
        {"HongKong Time", "HongKong Tijd",  &hongKong},
        {"Speak Time", "Spreek tijd",  &startTalkingClock},
        {"Return", "Terug", &returnFromTalkingClock}};


void launchTalkingClockMenu() {
    setMenu(menuItems, size, "| Time |", "| Klok |");
}

void dutchTime(){
    ESP_LOGI("Starting Dutch time now", "");
    getZone("TZ", "CET-1CEST,M3.5.0,M10.5.0/3");
    playTime();
};

void newZeland(){
    ESP_LOGI("Starting New Zeland time now", "");
    getZone("TZ", "NZST-12NZDT-13,M10.1.0/02:00:00,M3.3.0/03:00:00");
    playTime();
};

void hongKong(){
    ESP_LOGI("Starting Hong Kong time now!", "");
    getZone("TZ", "HKT-8");
    playTime();
};


void startTalkingClock(){
    ESP_LOGI("Starting a talking clock song now...", "");
    play_time();
};


void returnFromTalkingClock(){
    ESP_LOGI("RETURN", "");
    launchHomeMenu();
};
