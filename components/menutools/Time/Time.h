//
// Created by kroelie woelie on 16-3-2021.
//

#ifndef SMARTSPEAKER_TIME_H
#define SMARTSPEAKER_TIME_H

#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include <hd44780.h>
#include <pcf8574.h>
#include <string.h>
#include  "esp_peripherals.h"
#include "esp_wifi.h"
#include "periph_wifi.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_sntp.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "../menutools/LCD/LCD.h"

void time_init();
void getTime();
void setTime();
void initialize_sntp(void);
void setLocalSummerTime();
void setLocalWinterTime();
void play_time();
#endif //SMARTSPEAKER_TIME_H
