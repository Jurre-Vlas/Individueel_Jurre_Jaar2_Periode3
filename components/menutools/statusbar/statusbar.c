#include <hd44780.h>
#include <pcf8574.h>
#include <esp_log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "statusbar_icons.c"
#include "../LCD/LCD.h"
#include "../Time/Time.h"
#include "../../wifiController/wifiController.h"


#define STATUSBAR_UPDATEDELAY_MS 100
#define STATUSBAR_WAIT_COUNT 3

static const char *TAG = "Statusbar";

void statusbar_init() {
    //Upload characters to LCD
    lcdUploadChar(BLUETOOTH_ICON, 0); // \x08
    lcdUploadChar(WIRELESS_ICON, 1);  // \x09
    lcdUploadChar(PLAY_ICON, 2);     // \x0A
    lcdUploadChar(OK_ICON, 3);      // \x0B
    lcdUploadChar(PAUSE_ICON, 4);    // \x0C
    writeToLine("\x0A              \x08\x0B \x09\x0B", 0);
}

//TODO update bluetooth
bool bluetooth_stat = false;
bool wifi_stat = false;
bool bluetooth_buff = false;
bool wifi_buff= false;

// bluetooth icon OK_icon wireless OK-icon
void wait() {
    vTaskDelay(30 / portTICK_PERIOD_MS);
};

void statusbar_update() {
    if (bluetooth_stat != bluetooth_buff) {
        writeToLineAndCol(bluetooth_stat ? "\x0B" : "x", 0, 16);
        bluetooth_buff = bluetooth_stat;
    }
    if (wifi_stat != wifi_buff) {
        writeToLineAndCol(wifi_stat ? "\x0B" : "x", 0, 19);
        wifi_buff = wifi_stat;
    }
    getTime();
}

void statusbar_update_task(void *pvParameters) {
    writeToLine("Mon 00:00:00   \x08\x0B \x09\x0B", 0);

    writeToLineAndCol(bluetooth_stat ? "\x0B" : "x", 0, 16);
    writeToLineAndCol(wifi_stat ? "\x0B" : "x", 0, 19);

    bluetooth_buff = bluetooth_stat;
    wifi_buff = wifi_stat;
    timeInit();
    while (1) {
//        ESP_LOGD(TAG, "Updating statusbar");
        wifi_stat = getWifiStatus();
        statusbar_update();
        vTaskDelay(STATUSBAR_UPDATEDELAY_MS / portTICK_PERIOD_MS);
    }
}
