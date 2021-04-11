//
// Created by Mick on 02/03/2021.
//

#ifndef MENU_HOME_H
#define MENU_HOME_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "internetradio.h"
#include "bluetooth.h"
#include "klok.h"
#include "mp3.h"
#include "whitenoise.h"
#include "reminders.h"
#include "MenuItem.h"
#include "LCD/LCD.h"
#include "settings.h"
#include "weather.h"

#include "esp_log.h"

//includes for all the menutools's


void launchHomeMenu();
void internetRadio();
void bluetooth();
void talkingClock();
void mp3();
void whiteNoise();
void reminders();
void suspendHome();
void settings();
void weather();
void terminateHome();


#endif //MENU_HOME_H
