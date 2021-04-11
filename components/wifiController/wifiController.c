#include "wifiController.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <pcf8574.h>
#include <string.h>
#include "esp_peripherals.h"
#include "periph_wifi.h"
#include "board.h"
#include "esp_log.h"
#include "esp_netif.h"

static const char *TAG = "wifiController";

static periph_wifi_cfg_t wifi_cfg = {
        .ssid = "iPhone",
        .password = "jurre1234"
};
esp_periph_handle_t wifi_handle;
void wifi_init(esp_periph_set_handle_t peripherals_pool) {
    // Initialize the network stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Connect to the wifi using the variables set in the menuconfig
    ESP_LOGI(TAG, "Connecting to WiFi...");
    wifi_handle = periph_wifi_init(&wifi_cfg);
    esp_periph_start(peripherals_pool, wifi_handle);
    // We wait until the wifi is connected so we dont try to read data that isnt available yet.
    periph_wifi_wait_for_connected(wifi_handle, portMAX_DELAY);
    ESP_LOGI(TAG, "Wifi Connected");
}

bool getWifiStatus() {
    if (periph_wifi_is_connected(wifi_handle) == PERIPH_WIFI_CONNECTED){
        return true;
    }else{
        return false;
    }
}
