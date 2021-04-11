idf_component_register(
        SRCS "wifiController.c"
        INCLUDE_DIRS .
        REQUIRES hd44780 pcf8574 freertos esp_peripherals
)