//
// Created by Davy on 15-3-2021.
//

#ifndef SMARTSPEAKER_BLUETOOTH_H
#define SMARTSPEAKER_BLUETOOTH_H

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>

#include "MenuItem.h"
#include "home.h"
#include "LCD/LCD.h"

#include "esp_log.h"

void launchBluetoothMenu();
void connectDevice();
void disconnectDevice();
void returnFromBluetooth();

#endif //SMARTSPEAKER_BLUETOOTH_H
