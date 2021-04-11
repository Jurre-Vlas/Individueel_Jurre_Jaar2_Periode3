//
// Created by kroelie woelie on 11-4-2021.
//

#ifndef SMARTSPEAKER_WEATHER_H
#define SMARTSPEAKER_WEATHER_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

void launchWeatherMenu();
void returnFromWeather();

#endif //SMARTSPEAKER_WEATHER_H
