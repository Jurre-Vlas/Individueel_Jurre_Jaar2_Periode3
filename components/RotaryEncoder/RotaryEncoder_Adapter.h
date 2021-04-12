#ifndef RotaryEncoder_Adapter_H
#define RotaryEncoder_Adapter_H

#include "esp_err.h"

typedef void(*commandLeft_t)(); // void function pointer.
typedef void(*commandright_t)(); // void function pointer.
typedef void(*commandpress_t)(); // void function pointer.

// void function pointers as callbacks
typedef struct{
    commandLeft_t left;
    commandright_t right;
    commandpress_t press;
}commands_t;

/**
 * Initializes the adapter.
 * @param void_Function_Calls callbacks as defined in struct.
 * @return error code.
 */
esp_err_t RotaryEncoder_AdapterInit(commands_t void_Function_Calls);

/**
 * Frees the adapter from memory.
 * @return error code.
 */
esp_err_t RotaryEncoder_AdapterFree();

#endif