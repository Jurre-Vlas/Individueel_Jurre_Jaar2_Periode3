//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_WHITENOISE_H
#define SMARTSPEAKER_WHITENOISE_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

void launchWhiteNoiseMenu();

void PlayWN();

void StopWN();

void returnFromWN();

#endif //SMARTSPEAKER_WHITENOISE_H
