//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_KLOK_H
#define SMARTSPEAKER_KLOK_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"
#include "time.h"

void launchTalkingClockMenu();

void DutchTime();

void returnFromTalkingClock();

#endif //SMARTSPEAKER_KLOK_H
