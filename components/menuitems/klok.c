
#include "klok.h"

#include <stdio.h>
#include <sys/time.h>
#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"
#include "time.h"

// size of MenuItem
static int size = 6;


static MenuItem menuItems[] = {
        {"Dutch Time",     "Nederlandse Tijd",   &dutchTime},
        {"NewZeland Time", "Nieuw-Zeeland Tijd", &newZeland},
        {"HongKong Time",  "HongKong Tijd",      &hongKong},
        {"USA Time",     "Amerika tijd",        &unitedStates},
        {"Speak Time",     "Spreek tijd",        &startTalkingClock},
        {"Return",         "Terug",              &returnFromTalkingClock}
};

//launching Clock Menu
void launchClockMenu()
{
    setMenu(menuItems, size, "| Time |", "| Klok |");
}

//set & play Dutch time
void dutchTime()
{
    ESP_LOGI("Starting Dutch time now", "");
    getZone("TZ", "CET-1CEST,M3.5.0,M10.5.0/3");
    playTime();
};

//set & play New Zeland time
void newZeland()
{
    ESP_LOGI("Starting New Zeland time now", "");
    getZone("TZ", "NZST-12NZDT-13,M10.1.0/02:00:00,M3.3.0/03:00:00");
    playTime();
};

//set & play Hong Kong time
void hongKong()
{
    ESP_LOGI("Starting Hong Kong time now!", "");
    getZone("TZ", "HKT-8");
    playTime();
};

//set & play USA time
void unitedStates()
{
    ESP_LOGI("Starting USA time now!", "");
    getZone("TZ", "HAW10");
    playTime();
};

//play the time
void startTalkingClock()
{
    ESP_LOGI("Starting a talking clock song now...", "");
    playTime();
};

//return to Menu
void returnFromTalkingClock()
{
    ESP_LOGI("RETURN", "");
    launchHomeMenu();
};
