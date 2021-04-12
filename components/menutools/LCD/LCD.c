//
// Created by Davy on 2-3-2021.
// LCD class. You can use the methods in this class to initialise the lcd,
// write to the lcd, update the lcd, or clear the lcd.
// So everything that has to do with controlling the LCD.
//

//All includes can be found in the header file.
#include "LCD.h"

//Defining pins and adresses
#define SDA_GPIO 18
#define SCL_GPIO 23
#define I2C_ADDR 0x27
static i2c_dev_t pcf8574;

//Current selected item in the menu
//For example:
// Play - Stop - Return
//         ^ = item 1
int currentItem = 0;

//Size of the list of menu items.
static int itemListSize = 0;
MenuItem *itemListPtr;

//Current language. 1 is Dutch and 0 is English.
int currentLanguage = 0;

//Handle for the semaphore
SemaphoreHandle_t xSemaphore = NULL;

// Adapter between our code and the expander.
static esp_err_t write_lcd_data(const hd44780_t *lcd, uint8_t data) {
    return pcf8574_port_write(&pcf8574, data);
}

//Creating the LCD config.
static hd44780_t lcd = {
        .write_cb = write_lcd_data, // use callback to send data to LCD by I2C GPIO expander
        .font = HD44780_FONT_5X8,
        .lines = 4,
        .pins = {
                .rs = 0,
                .e  = 2,
                .d4 = 4,
                .d5 = 5,
                .d6 = 6,
                .d7 = 7,
                .bl = 3
        }
};

//Initialize LCD screen.
void initLCD() {
    memset(&pcf8574, 0, sizeof(i2c_dev_t));
    ESP_ERROR_CHECK(pcf8574_init_desc(&pcf8574, 0, I2C_ADDR, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(hd44780_init(&lcd));
    hd44780_switch_backlight(&lcd, true);
    xSemaphore = xSemaphoreCreateMutex();
    ESP_LOGI("LCD DRIVER", "Done with init/creating mutex");
}

//Set language to English
void setLangToEN() {
    currentLanguage = 0;
};

//Set language to Dutch
void setLangToNL() {
    currentLanguage = 1;
};


//WritetoLine method, give some text and the line where it should be written.
void writeToLine(char *text, int lineNumber) {
    if (xSemaphore != NULL) {
        /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
        if (xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE) {
            /* We were able to obtain the semaphore and can now access the
            shared resource. */

            //If we obtain the semaphore (so no one else is accessing this)
            // We can write to the screen.
            hd44780_gotoxy(&lcd, 0, lineNumber);
            hd44780_puts(&lcd, text);

            /* We have finished accessing the shared resource.  Release the
            semaphore. */
            xSemaphoreGive(xSemaphore);
        } else {
            /* We could not obtain the semaphore and can therefore not access
            the shared resource safely. */
            ESP_LOGI("LCD DRIVER", "WE FAILED IN WRITING TO LINE WITH THE MUTEX");
        }
    }

}

//writeToLineAndCol method, give some text and the line where it should be written.
// Also give the column, which is where in the line we should start.
void writeToLineAndCol(char *text, int lineNumber, int column) {
    if (xSemaphore != NULL) {
        /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
        if (xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE) {
            /* We were able to obtain the semaphore and can now access the
            shared resource. */

            //If we obtain the semaphore (so no one else is accessing this)
            // We can write to the screen.
            hd44780_gotoxy(&lcd, column, lineNumber);
            hd44780_puts(&lcd, text);

            /* We have finished accessing the shared resource.  Release the
            semaphore. */
            xSemaphoreGive(xSemaphore);
        } else {
            /* We could not obtain the semaphore and can therefore not access
            the shared resource safely. */
            ESP_LOGI("LCD DRIVER", "WE FAILED IN WRITING TO LINE WITH THE MUTEX");
        }
    }

}

//Clears a given line.
void clearLine(int lineNumber) {
    if (xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE) {
        /* We were able to obtain the semaphore and can now access the
        shared resource. */

        hd44780_gotoxy(&lcd, 0, lineNumber);
        hd44780_puts(&lcd, "                    ");

        /* We have finished accessing the shared resource.  Release the
        semaphore. */
        xSemaphoreGive(xSemaphore);
    } else {
        /* We could not obtain the semaphore and can therefore not access
        the shared resource safely. */
        ESP_LOGI("LCD DRIVER", "WE FAILED IN WRITING TO LINE WITH THE MUTEX");
    }

}

//Used for uploading special characters and making them writeable.
//For example the Bluetooth icon.
void lcdUploadChar(uint8_t ICON[], int number) {
    hd44780_upload_character(&lcd, number, ICON);
}

//
void setMenu(MenuItem menuItems[], int size, char descrLineEN[],  char descrLineNL[]) {
    currentItem = 0;
    itemListSize = size;

    itemListPtr = &menuItems[0];

    for (int i = 1; i < 3; ++i) {
        clearLine(i);
    }

    if (currentLanguage == 0) {
        writeToLine(descrLineEN, 1);
    }

    if (currentLanguage == 1) {
        writeToLine(descrLineNL, 1);
    }




    writeToLine("         ^         ", 3);
    //Writing the first line
    writeToLineAndCol("<-", 2, 0);

    if (currentLanguage == 0) {
        writeToLineAndCol(itemListPtr->nameEN, 2, 3);
    }

    if (currentLanguage == 1) {
        writeToLineAndCol(itemListPtr->nameNL, 2, 3);
    }

    writeToLineAndCol("->", 2, 18);
}

void scrollRight() {
    if (currentItem >= itemListSize - 1) {
        //do nothing
    } else {
        currentItem = currentItem + 1;
        itemListPtr++;
        clearLine(2);


        writeToLineAndCol("<-", 2, 0);


        if (currentLanguage == 0) {
            writeToLineAndCol(itemListPtr->nameEN, 2, 3);
        }

        if (currentLanguage == 1) {
            writeToLineAndCol(itemListPtr->nameNL, 2, 3);
        }

        writeToLineAndCol("->", 2, 18);
    }
}

void scrollLeft() {
    if (currentItem == 0) {
        //do nothing
    } else {
        currentItem = currentItem - 1;
        itemListPtr--;
        clearLine(2);
        writeToLineAndCol("<-", 2, 0);

        if (currentLanguage == 0) {
            writeToLineAndCol(itemListPtr->nameEN, 2, 3);
        }

        if (currentLanguage == 1) {
            writeToLineAndCol(itemListPtr->nameNL, 2, 3);
        }
        writeToLineAndCol("->", 2, 18);
    }
}


void getSelectedOption() {
    char text[50] = "";

    if (currentLanguage == 0) {
        sprintf(text, "%s", itemListPtr->nameEN);
        (itemListPtr->handle)(NULL);
    }

    if (currentLanguage == 1) {
        sprintf(text, "%s", itemListPtr->nameNL);
        (itemListPtr->handle)(NULL);
    }
}


