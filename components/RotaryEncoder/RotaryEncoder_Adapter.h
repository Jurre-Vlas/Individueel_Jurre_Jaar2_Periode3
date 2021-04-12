#ifndef RotaryEncoder_Adapter_H
#define RotaryEncoder_Adapter_H

#include "RotaryEncoder_Driver.h"
#include "stdbool.h"
#include "freertos/queue.h"

#define SDA_GPIO 18
#define SCL_GPIO 23

#define queueSize 20
#define itemSize sizeof(uint8_t)

typedef void(*commandLeft_t)();
typedef void(*commandright_t)();
typedef void(*commandpress_t)();

QueueHandle_t rotaryQueue;

typedef struct{
    commandLeft_t left;
    commandright_t right;
    commandpress_t press;
}commands_t;

i2c_dev_t dev;
commands_t commands;

esp_err_t RotaryEncoder_get_command(uint8_t val);
esp_err_t RotaryEncoder_get_diff(uint16_t *val);
esp_err_t RotaryEncoder_AdapterInit(commands_t void_Function_Calls);
esp_err_t RotaryEncoder_AdapterFree();
void CHECK_INITIALIZED();

#endif