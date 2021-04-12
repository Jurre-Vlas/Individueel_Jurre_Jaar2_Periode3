//
// Created by Davy on 19-3-2021.
//

#ifndef SMARTSPEAKER_SETTINGS_H
#define SMARTSPEAKER_SETTINGS_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"
#include "../menutools/Time/Time.h"

void launchSettingsMenu();
void setLanguageNL();
void setLanguageEN();
void returnFromSettings();


#endif //SMARTSPEAKER_SETTINGS_H
