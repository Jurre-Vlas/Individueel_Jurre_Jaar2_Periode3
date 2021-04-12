#include "RotaryEncoder_Driver.h"

//region Memory Allocation / Thread Safety

static esp_err_t read_port(i2c_dev_t *dev, int8_t reg, uint8_t *val)
{
    I2C_DEV_TAKE_MUTEX(dev);
    I2C_DEV_CHECK(dev, i2c_dev_read(dev, &reg, sizeof(int8_t), val, 1));
    I2C_DEV_GIVE_MUTEX(dev);

    return ESP_OK;
}

static esp_err_t write_port(i2c_dev_t *dev, int8_t reg ,uint8_t val)
{
    I2C_DEV_TAKE_MUTEX(dev);
    I2C_DEV_CHECK(dev, i2c_dev_write(dev, &reg, sizeof(int8_t), &val, 1));
    I2C_DEV_GIVE_MUTEX(dev);

    return ESP_OK;
}

esp_err_t RotaryEncoder_init(i2c_dev_t *dev, i2c_port_t port, uint8_t addr, int sda_gpio, int scl_gpio){
    dev->port = port;
    dev->addr = addr;
    dev->cfg.sda_io_num = sda_gpio;
    dev->cfg.scl_io_num = scl_gpio;
#if HELPER_TARGET_IS_ESP32
    dev->cfg.master.clk_speed = I2C_FREQ_HZ;
#endif

    return i2c_dev_create_mutex(dev);
}

esp_err_t RotaryEncoder_free(i2c_dev_t *dev)
{
    return i2c_dev_delete_mutex(dev);
}

//endregion

//region 8Bit

esp_err_t RotaryEncoder_port_read(i2c_dev_t *dev, uint8_t reg, uint8_t *val)
{
    return read_port(dev,reg,val);
}

esp_err_t RotaryEncoder_port_write(i2c_dev_t *dev, uint8_t reg, uint8_t val)
{
    return write_port(dev,reg,val);
}
//endregion

//region 16Bit

esp_err_t RotaryEncoder_port_read16(i2c_dev_t *dev, uint8_t reg, uint16_t *val)
{
    //define bits for 2 registers
    uint8_t LSB = 0x00;
    uint8_t MSB = 0x00;
    //get values of both registers
    read_port(dev,reg,&LSB);
    read_port(dev,reg+1,&MSB);

    //shift them into eachother and send them back
    *val = ((uint16_t)MSB << 8 | LSB);
    
    return ESP_OK;
}

esp_err_t RotaryEncoder_port_write16(i2c_dev_t *dev, uint8_t reg, uint16_t val)
{
    // writes to the 8bit regs separately.
    write_port(dev,reg,(uint8_t)val << 8); //write to the first reg.
    write_port(dev,reg+1,(uint8_t)val >> 8); //write to the second reg.
    return ESP_OK;
}

//endregion