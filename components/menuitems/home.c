#include "home.h"

static int size = 7;

static MenuItem menuItems[] = {
        {"Radio", "Radio",
         &internetRadio},
        {"Bluetooth", "Bluetooth",
         &bluetooth},
        {"Clock", "Klok",
         &talkingClock},
        {"MP3 player", "MP3 speler",
         &mp3},
        {"Whitenoise", "Rustgeluid",
         &whiteNoise},
        {"Reminders", "Herinneringen",
         &reminders},
        {"Settings", "Instellingen",
         &settings}};

/**
 * Launches the Home menutools.
 */
void launchHomeMenu() {
    setMenu(menuItems, size, "| Select a menu. |", "| Kies een menu |");
}

/**
 * Responds to the selection of the 'Internet Radio' item".
 */
void internetRadio(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD internetRadio \n");
    launchInternetRadioMenu();

}

/**
 * Responds to the selection of the 'Bluetooth' item".
 */
void bluetooth(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD bluetooth \n");
    launchBluetoothMenu();
}

/**
 * Responds to the selection of the 'Talking Clock' item".
 */
void talkingClock(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD Talking clock \n");
    launchClockMenu();
}

/**
 * Responds to the selection of the 'Mp3' item".
 */
void mp3(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD mp3 \n");
    launchMP3Menu();
}

/**
 * Responds to the selection of the 'White Noise' item".
 */
void whiteNoise(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD whiteNoise \n");
    launchWhiteNoiseMenu();
}

/**
 * Responds to the selection of the 'Meldingen' item".
 */
void reminders(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD reminders \n");
    launchRemindersMenu();
}

void settings(void *args) {
    ESP_LOGI("METHOD CALLED", "WE CALLED METHOD settings \n");
    launchSettingsMenu();
}

/**
 * Suspends the home screen for temporary termination, but leaves the current state in memory.
 */
void suspendHome(void *args) {
    //todo save home state.
}

/**
 * Terminates all active home tasks.
 */
void terminateHome() {
}