/*
 * PCA9685_servo.c
 *
 * Created: 19.09.2018 20:42:26
 *  Author: Filip
 */ 
#include "PCA9685_servo.h"
#include <avr/io.h>
#include "../i2c/i2c.h"
#include <util/delay.h>

void initServosI2C()
{
	i2cInit();
	_delay_ms(5);
	i2cWriteRegister(PCA9685_I2C_ADDR, PCA9685_PRE_SCALE, 0x79);
	i2cWriteRegister(PCA9685_I2C_ADDR, PCA9685_MODE1, 0b00000001);
	_delay_ms(5);
}

void setServoPWM(uint8_t servo, uint16_t duty)
{
	uint8_t reg_low = 0x08 + servo * 4;
	uint8_t reg_high = 0x09 + servo * 4;
	duty &= 0x0fff;
	i2cWriteRegister(PCA9685_I2C_ADDR, reg_low, (uint8_t)duty);
	i2cWriteRegister(PCA9685_I2C_ADDR, reg_high, (uint8_t)(duty >> 8));
}
