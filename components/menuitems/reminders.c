//
// Created by Davy on 15-3-2021.
//
#include "reminders.h"

static int size = 2;

static MenuItem menuItems[] = {
        {"Homework 20SEC", "Huiswerk 20SEC", &setHomeWorkReminder},
        {"Return", "Terug", &returnFromWN}};


void launchRemindersMenu() {
    setMenu(menuItems, size, "| Reminders |", "| Herinneringen |");
}

void homeworkReminder(){
    vTaskDelay(20000 / portTICK_PERIOD_MS);
    launchHomeWorkPopup();
    vTaskSuspend( NULL );
}

void setHomeWorkReminder(){
    ESP_LOGI("METHOD CALLED", "SET setHomeWorkReminder \n");
    xTaskCreate( homeworkReminder, "homeworkReminder", 2048, NULL, 4, NULL);
};

void returnFromReminders(){
    ESP_LOGI("RETURN", "");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
};
