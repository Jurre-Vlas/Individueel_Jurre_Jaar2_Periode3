//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_KARAOKE_H
#define SMARTSPEAKER_KARAOKE_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

void launchKaraokeMenu();

void StartKaraoke();

void returnFromKaraoke();

#endif //SMARTSPEAKER_KARAOKE_H
