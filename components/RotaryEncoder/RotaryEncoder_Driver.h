#ifndef RotaryEncoder_H
#define RotaryEncoder_H

#include <stdint.h>
// Error library
#include "esp_err.h"
// FreeRTOS (for delay)

#include "i2cdev.h"
#include "esp_log.h"

// I2C_ADDR 0x3F
#define I2C_FREQ_HZ 100000

typedef enum{
    INT_ENABLE = 0x04,             //Set the bit to 1 to enable the interrupt for the button or encoder.
    LED_BRIGHTNESS_RED = 0x0D,     //Value between 0 and 255 representing the brightness of the red LED
    LED_BRIGHTNESS_GRN = 0x0E,     //Value between 0 and 255 representing the brightness of the green LED
    LED_BRIGHTNESS_BLU = 0x0F,     //Value between 0 and 255 representing the brightness of the blue LED
    STAT = 0x01,                   //Status of the Qwiic Twist. 3:0 = buttonPressed(3),
    //buttonClicked(2), buttonInterrupt(1), encoderInterrupt(0).
    //Events must be cleared by user.
    FW_VERSION_MSB = 0x02,         //The current firmware version
    FW_VERSION_LSB = 0x03,
    RE_COUNT_LSB = 0x05,
    RE_COUNT_MSB = 0x06,
    RE_DIFF_LSB = 0x07,
    RE_DIFF_MSB = 0x08,
    RE_TSLM_LSB = 0x09,
    RE_TSLM_MSB = 0x0A,
    RE_TSLB_LSB = 0x0B,
    RE_TSLB_MSB = 0x0C,
    LED_CON_RED_LSB = 0x10,
    LED_CON_RED_MSB = 0x11,
    LED_CON_GRN_LSB = 0x12,
    LED_CON_GRN_MSB = 0x13,
    LED_CON_BLU_LSB = 0x14,
    LED_CON_BLU_MSB = 0x15,
    TRN_INT_TO_LSB = 0x16,
    TRN_INT_TO_MSB = 0x17,
}RE_reg_t;

esp_err_t RotaryEncoder_init(i2c_dev_t *dev, i2c_port_t port, uint8_t addr, int sda_gpio, int scl_gpio);
esp_err_t RotaryEncoder_free(i2c_dev_t *dev);
esp_err_t RotaryEncoder_port_read(i2c_dev_t *dev, uint8_t reg, uint8_t *val);
esp_err_t RotaryEncoder_port_write(i2c_dev_t *dev, uint8_t reg, uint8_t val);
esp_err_t RotaryEncoder_port_read16(i2c_dev_t *dev, uint8_t reg, uint16_t *val);
esp_err_t RotaryEncoder_port_write16(i2c_dev_t *dev, uint8_t reg, uint16_t val);


#endif
