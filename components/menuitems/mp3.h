//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_MP3_H
#define SMARTSPEAKER_MP3_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

void launchMP3Menu();

void Play();

void Stop();

void returnFromMp3();

#endif //SMARTSPEAKER_MP3_H
