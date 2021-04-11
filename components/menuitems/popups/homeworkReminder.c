//
// Created by Davy on 22-3-2021.
//

#include "homeworkReminder.h"

static int size = 1;

static MenuItem menuItems[] = {
        {"CONFIRM", "BEVESTIG", &returnFromWN}};

void launchHomeWorkPopup() {
    setMenu(menuItems, size, "!REMINDER - SCHOOL!", "!HERINNER - SCHOOL!");
}

void returnFromHomeWorkPopup(){
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};