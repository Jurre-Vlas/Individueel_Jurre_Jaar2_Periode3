#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <sys/time.h>
#include <hd44780.h>
#include <pcf8574.h>
#include <string.h>
#include "periph_sdcard.h"
#include "LCD/LCD.h"
#include "home.h"
#include "RotaryEncoder_Adapter.h"
#include "statusbar/statusbar.h"
#include "wifiController.h"
#include "AudioSetup/AudioSetup.h"
#include "audioRecognition.h"
#include "wifiController.h"


#define SDA_GPIO 18
#define SCL_GPIO 23
#define I2C_ADDR 0x27
static const char *TAG = "Main";
static void nvsflash_init();
static void sdcard_init();
static esp_periph_set_handle_t peripherals_pool;

void initializeRotary() {
    commands_t void_func_ptr;
    void_func_ptr.left = &scrollLeft;;
    void_func_ptr.right = &scrollRight;;
    void_func_ptr.press = &getSelectedOption;

    RotaryEncoder_AdapterInit(void_func_ptr);
}

void initializeStatusBar() {
    statusbar_init();
    xTaskCreate( statusbar_update_task, "statusbarupdatetask", 2048, NULL, 2, NULL);
}

/*end of example*/
void app_main() {
    ESP_ERROR_CHECK(i2cdev_init());

    // Configure peripherals
    ESP_LOGI(TAG, "Creating peripheral pool");
    esp_periph_config_t periph_cfg = DEFAULT_ESP_PERIPH_SET_CONFIG();
    peripherals_pool = esp_periph_set_init(&periph_cfg);

    nvsflash_init();
    ESP_LOGI(TAG, "done nvsflash");
    wifi_init(peripherals_pool);
    ESP_LOGI(TAG, "done wifi init");
    sdcard_init();
    ESP_LOGI(TAG, "done SD init");

    initLCD();
    ESP_LOGI(TAG, "done lcd init");

    setupAudio(&peripherals_pool);
    ESP_LOGI(TAG, "done audio setup");

    //START OF ROTARY TASK
    initializeRotary();

    launchHomeMenu();


    vTaskDelay(1000 / portTICK_PERIOD_MS);

    //START OF STATUS BAR TASK
    initializeStatusBar();
    audioRecognition_init();
}

void sdcard_init(){
    periph_sdcard_cfg_t sd_cfg = {
        .card_detect_pin = 34,
        .mode = SD_MODE_1_LINE
    };

    esp_periph_handle_t sd_handle = periph_sdcard_init(&sd_cfg);
    esp_periph_start(peripherals_pool, sd_handle);

    //audio_board_sdcard_init(peripherals_pool, SD_MODE_1_LINE);
}

void nvsflash_init() {
    ESP_LOGI(TAG, "NVS flash init");
    // We use the nvs flash as a buffer to store the mp3 stream data
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_LOGW(TAG, "NVS flash was truncated, restoring");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_LOGI(TAG, "Done initiating NVS flash");
}

