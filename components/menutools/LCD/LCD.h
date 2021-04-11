#ifndef MENU_LCD_H
#define MENU_LCD_H

#include <stdio.h>
#include <string.h>
#include "hd44780.h"
#include "pcf8574.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "statusbar/statusbar.h"
#include <stddef.h>
#include "MenuItem.h"

struct LcdQueueItem
{
    uint8_t line;
    uint8_t pos;
    char *text;

};

void writeToLine(char *text, int lineNumber);
void writeToLineAndCol(char *text, int lineNumber, int column);
void initLCD();
void scrollLeft();
void scrollRight();
void setMenu(MenuItem menuItems[], int size, char descrLineEN[],  char descrLineNL[]);
void getSelectedOption();
void clearLine(int lineNumber);
void lcdUploadChar(uint8_t ICON[], int number);
void setLangToEN();
void setLangToNL();


#endif //end