#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>


LOG_MODULE_REGISTER(test_as5600);
#define I2C0_NODE DT_NODELABEL(as5600)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

void write_byte_i2c(uint8_t *data);
void read_byte_i2c(uint8_t *data);

int main(void)
{

        if (!device_is_ready(dev_i2c.bus))
        {
                LOG_ERR("I2C bus %s is not ready!\n\r", dev_i2c.bus->name);
                return 0;
        }

        k_msleep(20);

        uint8_t address_angle_11_8 = 0x0E;
        uint8_t address_angle_7_0 = 0x0F;

        while (1)
        {
                uint8_t data_angle_11_8 = 0;
                uint8_t data_angle_7_0 = 0;

                write_byte_i2c(&address_angle_11_8);
                read_byte_i2c(&data_angle_11_8);
                k_msleep(5);
                write_byte_i2c(&address_angle_7_0);
                read_byte_i2c(&data_angle_7_0);
                uint16_t angle = ( ((data_angle_11_8 & 0x0F) << 8) | (data_angle_7_0));
                LOG_INF("11_8: %u, 7_0: %u,  Angle: %u", data_angle_11_8, data_angle_7_0, angle);

                k_msleep(100);

       }

        return 0;
}

void write_byte_i2c(uint8_t *data)
{
        int ret = i2c_write_dt(&dev_i2c, data, 1);
        if (ret != 0)
        {
                LOG_ERR("Failed to write to I2C device address %x at reg. %u \n\r", dev_i2c.addr, *data);
        }
}

void read_byte_i2c(uint8_t *data)
{
        int ret;

        ret = i2c_read_dt(&dev_i2c, data, 1);
        if (ret != 0)
        {
                LOG_ERR("Failed to read from I2C device address %x at Reg. %u \n\r", dev_i2c.addr, *data);
        }
}
