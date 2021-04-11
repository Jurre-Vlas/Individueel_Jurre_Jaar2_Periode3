//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_INTERNETRADIO_H
#define SMARTSPEAKER_INTERNETRADIO_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

//Audio incls

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "audioController.h"

void launchInternetRadioMenu();

void NPORadio1();

void NPORadio2();

void NPO3FM();

void RADIO10();

void QMusic();

void SkyRadio();

void Radio538();

void returnFromIR();

#endif //SMARTSPEAKER_INTERNETRADIO_H
