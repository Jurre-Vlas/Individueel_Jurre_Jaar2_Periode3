#include <hd44780.h>
#include <pcf8574.h>
#include <esp_log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "statusbar_icons.c"
#include "../menutools/LCD/LCD.h"
#include "../menutools/Time/Time.h"

#define STATUSBAR_UPDATEDELAY_MS 3000
#define STATUSBAR_WAIT_COUNT 3

static const char *TAG = "Statusbar";
static int i = 0;

void statusbar_init() {
    //Upload characters to LCD
    lcdUploadChar(BLUETOOTH_ICON, 0); // \x08
    lcdUploadChar(WIRELESS_ICON, 1);  // \x09
    lcdUploadChar(PLAY_ICON, 2);     // \x0A
    lcdUploadChar(OK_ICON, 3);      // \x0B
    lcdUploadChar(PAUSE_ICON, 4);    // \x0C
}


// bluetooth icon OK_icon wireless OK-icon
void wait() {
    vTaskDelay(30 / portTICK_PERIOD_MS);
};

void statusbar_update() {
    //TODO: MAAK WI-FI EN BT UP-TO-DATE EN VOEG DE TIJD TOE
//    clearLine(0);
//    getTime(0);
//    wait();
//    writeToLineAndCol("\x08", 0, 10);
//    wait();
//    writeToLineAndCol("\x09", 0, 12);
//    wait();
//    writeToLineAndCol("\x0A", 0, 14);
//    wait();
//    writeToLineAndCol("\x0C", 0, 18);
//    wait();
//    vTaskDelay(3000 / portTICK_PERIOD_MS);

    clearLine(0);
    getTime();
    wait();
    writeToLineAndCol("\x08", 0, 14);
    wait();
    writeToLineAndCol("\x0B", 0, 15);
    wait();
    writeToLineAndCol("\x09", 0, 17);
    wait();
    writeToLineAndCol("\x0B", 0, 18);
    wait();
    vTaskDelay(470 / portTICK_PERIOD_MS);

}

void statusbar_update_task() {
    time_init();
    while (1) {
        ESP_LOGD(TAG, "Updating statusbar");
        statusbar_update();
        vTaskDelay(470 / portTICK_PERIOD_MS);
    }
}
