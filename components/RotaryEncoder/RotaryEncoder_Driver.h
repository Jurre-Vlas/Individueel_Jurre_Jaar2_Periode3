#ifndef RotaryEncoder_H
#define RotaryEncoder_H

#include "esp_err.h"
#include "i2cdev.h"

typedef enum{
    STAT = 0x01,                   //Status of the Qwiic Twist. 3:0 = buttonPressed(3),
    RE_COUNT_LSB = 0x05,
}RE_reg_t;

//region Memory Allocation / Thread Safety
/**
 * Initializes the Rotary Driver.
 * @param dev Thread safe handle for I2C.
 * @param port The I2C port to communicate with.
 * @param addr Address of the device.
 * @param sda_gpio SDA address of the GPIO PIN.
 * @param scl_gpio SLC address of the GPIO PIN.
 * @return Error code.
 */
esp_err_t RotaryEncoder_init(i2c_dev_t *dev, i2c_port_t port, uint8_t addr, int sda_gpio, int scl_gpio);

/**
 * Thread safe helper function for reading data from the rotary.
 * @param dev Thread safe handle for I2C.
 * @param reg Registry address.
 * @param val Value to fill with raw data.
 * @return
 */
esp_err_t RotaryEncoder_free(i2c_dev_t *dev);
//endregion

//region 8Bit
/**
 * Reads the 8-Bit raw value from the Rotary Encoder.
 * @param dev Thread safe handle for I2C.
 * @param reg Registry address.
 * @param val Value to fill with raw data.
 * @return Error code.
 */
esp_err_t RotaryEncoder_port_read(i2c_dev_t *dev, uint8_t reg, uint8_t *val);

/**
 * writes the 8-Bit raw value to the Rotary Encoder.
 * @param dev Thread safe handle for I2C.
 * @param reg Registry address.
 * @param val Value to fill with raw data.
 * @return Error code.
 */
esp_err_t RotaryEncoder_port_write(i2c_dev_t *dev, uint8_t reg, uint8_t val);
//endregion

//region 16Bit
/**
 * Reads the 16-Bit raw value from the Rotary Encoder.
 * @param dev Thread safe handle for I2C.
 * @param reg Registry address.
 * @param val Value to fill with raw data.
 * @return Error code.
 */
esp_err_t RotaryEncoder_port_read16(i2c_dev_t *dev, uint8_t reg, uint16_t *val);

/**
 * writes the 16-Bit raw value to the Rotary Encoder.
 * @param dev Thread safe handle for I2C.
 * @param reg Registry address.
 * @param val Value to fill with raw data.
 * @return Error code.
 */
esp_err_t RotaryEncoder_port_write16(i2c_dev_t *dev, uint8_t reg, uint16_t val);
//endregion
#endif
