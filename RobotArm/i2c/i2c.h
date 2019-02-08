/*
 * i2c.h
 *
 * Created: 19.09.2018 18:28:06
 *  Author: Filip
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define F_CPU 1000000

#define I2C_START 0x08
#define I2C_START_REPEATED 0x10
#define I2C_ADDR_WRITE_ACK 0x18
#define I2C_ADDR_WRITE_NACK 0x20
#define I2C_DATA_SENT_ACK 0X28
#define I2C_DATA_SENT_NACK 0x30
#define I2C_ARBITRATION_LOST 0x38
#define I2C_ADDR_READ_ACK 0x40
#define I2C_ADDR_READ_NACK 0x48
#define I2C_DATA_RECEIVED_ACK 0X50
#define I2C_DATA_RECEIVED_NACK 0x58

#define I2C_STATUS_MASK 0b11111000
#define I2C_OK 0
#define F_SCL 100000


void i2cInit();
uint8_t i2cStart();
void i2cStop();
void i2cSend(uint8_t data);
uint8_t i2cSendAddress(uint8_t address);
uint8_t i2cSendData(uint8_t data);
void i2cWriteRegister(uint8_t dev_address, uint8_t dev_register, uint8_t data);
void i2cReadRegister(uint8_t dev_address, uint8_t dev_register, uint8_t * data);
#endif /* I2C_H_ */