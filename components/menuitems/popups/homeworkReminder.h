//
// Created by Davy on 22-3-2021.
//

#ifndef SMARTSPEAKER_HOMEWORKREMINDER_H
#define SMARTSPEAKER_HOMEWORKREMINDER_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include "../MenuItem.h"
#include "../home.h"
#include "../menutools/LCD/LCD.h"
#include "esp_log.h"

void launchHomeWorkPopup();

void returnFromHomeWorkPopup();

#endif //SMARTSPEAKER_HOMEWORKREMINDER_H
