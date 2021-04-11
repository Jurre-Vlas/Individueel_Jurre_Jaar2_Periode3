//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_REMINDERS_H
#define SMARTSPEAKER_REMINDERS_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"
#include "esp_log.h"

#include "popups/homeworkReminder.h"

void launchRemindersMenu();
void homeworkReminder();
void setHomeWorkReminder();
void setWorkOutReminder();
void returnFromReminders();

#endif //SMARTSPEAKER_REMINDERS_H
