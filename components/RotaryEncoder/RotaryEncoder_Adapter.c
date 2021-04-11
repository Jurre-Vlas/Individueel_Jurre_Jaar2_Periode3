#include "RotaryEncoder_Adapter.h"
#include "RotaryEncoder_Driver.h"
#include "esp_log.h"

#define SDA_GPIO 18
#define SCL_GPIO 23

i2c_dev_t dev;
commands_t commands;

void RotaryEncoder_Read();
esp_err_t RotaryEncoder_get_diff(uint16_t *val);
esp_err_t RotaryEncoder_get_command(uint8_t val);
esp_err_t RotaryEncoder_AdapterFree();

/**
 * Reads and processes raw 8-bit data from the Rotary Driver.
 */
void RotaryEncoder_Read() {
    uint8_t val = 0;
    while (1) {
        RotaryEncoder_port_read(&dev,STAT,&val);
        RotaryEncoder_port_write(&dev,STAT,0);
        if (val > 0) {
            RotaryEncoder_get_command(val);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/**
 * Interprets the 16-bit diff value and generates an action.
 * @param val diff value.
 * @return error code.
 */
esp_err_t RotaryEncoder_get_command(uint8_t val){
    uint16_t data = 0;
    switch (val)
    {
    case 1:
        RotaryEncoder_get_diff(&data);
        if(data > 0 && data < 1000)
        commands.right();
        else commands.left();
        break;
    case 4:
        commands.press();
        break;
    default:
        ESP_LOGI("Rotary Encoder", "Adapter read misfire with value: %d", val);
    }
    return ESP_OK;
}

/**
 * Interprets the raw 16-bit data received from the driver.
 * @param val raw value of rotary driver.
 * @return error code.
 */
esp_err_t RotaryEncoder_get_diff(uint16_t *val){
    RotaryEncoder_port_read16(&dev,RE_COUNT_LSB,val);
    RotaryEncoder_port_write16(&dev,RE_COUNT_LSB,0);
    return ESP_OK;
}

/**
 * Initializes the adapter.
 * @param void_Function_Calls callbacks as defined in struct.
 * @return error code.
 */
esp_err_t RotaryEncoder_AdapterInit(commands_t void_Function_Calls){
    RotaryEncoder_init(&dev,0,0x3F,SDA_GPIO,SCL_GPIO); // 0x3F is the address of the Rotary Encoder.
    commands = void_Function_Calls;

    xTaskCreate(RotaryEncoder_Read, "Rotary_read_task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    return ESP_OK;
}

/**
 * Frees the adapter from memory.
 * @return error code.
 */
esp_err_t RotaryEncoder_AdapterFree(){
    RotaryEncoder_free(&dev);
    return ESP_OK;
}

