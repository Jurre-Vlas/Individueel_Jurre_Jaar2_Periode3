//
// Created by kroelie woelie on 11-4-2021.
//


#include "weather.h"

static int size = 2;

static MenuItem menuItems[] = {
        {"Working", "het werkt", &launchWeatherMenu},
        {"Return", "Terug", &returnFromWeather}};


void launchWeatherMenu() {
    setMenu(menuItems, size, "| Weather |", "| Weer |");
}


void returnFromWeather() {
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};


