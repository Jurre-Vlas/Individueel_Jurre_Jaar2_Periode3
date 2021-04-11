//
// Created by Davy on 19-3-2021.
//

#include "settings.h"

static int size = 5;

static MenuItem menuItems[] = {
        {"Winter Time", "Winter tijd", &setWinterTime},
        {"Summer Time", "Zomer tijd",&setSummertime},
        {"Set Dutch", "Zet Nederlands", &setLanguageNL},
        {"Set English", "Zet Engels",&setLanguageEN},
        {"Return", "Terug", &returnFromSettings}};


void launchSettingsMenu() {
    setMenu(menuItems, size, "| Settings |", "| Instellingen |");
}

void setWinterTime() {
    setLocalSummerTime();
};

void setSummertime() {
    setLocalWinterTime();
};

void setLanguageNL() {
    setLangToNL();
    launchSettingsMenu();
};

void setLanguageEN() {
    setLangToEN();
    launchSettingsMenu();
};

void returnFromSettings() {
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};


