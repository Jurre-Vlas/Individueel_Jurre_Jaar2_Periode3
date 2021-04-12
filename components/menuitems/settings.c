//
// Created by Davy on 19-3-2021.
//

#include "settings.h"

static int size = 3;

static MenuItem menuItems[] = {
        {"Set Dutch", "Zet Nederlands", &setLanguageNL},
        {"Set English", "Zet Engels",&setLanguageEN},
        {"Return", "Terug", &returnFromSettings}};


void launchSettingsMenu() {
    setMenu(menuItems, size, "| Settings |", "| Instellingen |");
}

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


