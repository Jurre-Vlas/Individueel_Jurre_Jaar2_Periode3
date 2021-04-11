//
// Created by Davy on 15-3-2021.
//

#include "bluetooth.h"

static int size = 3;

static MenuItem menuItems[] = {
        {"Connect", "Verbinden", &connectDevice},
        {"Disconnect", "Verbreken", &disconnectDevice},
        {"Return", "Terug",  &returnFromBluetooth}};


void launchBluetoothMenu() {
    setMenu(menuItems, size, "| Select an option. |", "| Kies een optie |");
}

void connectDevice() {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD connectDevice \n");
}

void disconnectDevice() {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD disconnectDevice \n");
}

void returnFromBluetooth() {
    ESP_LOGI("RETURN", "WE CALLED METHOD RETURN \n");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
}