/*
 * i2c.c
 *
 * Created: 19.09.2018 18:39:07
 *  Author: Filip
 */ 

#include "i2c.h"

void i2cInit()
{
	TWCR = (1 << TWEN);
	TWBR = (F_CPU / F_SCL - 16) / 2;
}


uint8_t i2cStart()
{
	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
	uint8_t status = TWSR & I2C_STATUS_MASK;
	if (status == I2C_START || status == I2C_START_REPEATED)
		return I2C_OK;
	else 
		return status;
}

void i2cStop()
{
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
	while(TWCR & (1 << TWSTO));
}

void i2cSend(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
}

uint8_t i2cSendAddress(uint8_t address)
{
	i2cSend(address);
	uint8_t status = TWSR & I2C_STATUS_MASK;
	if(address & 0b00000001)
		return (status == I2C_ADDR_READ_ACK) ? I2C_OK : status;
	else
		return (status == I2C_ADDR_WRITE_ACK) ? I2C_OK : status;
}

uint8_t i2cSendData(uint8_t data)
{
	i2cSend(data);
	uint8_t status = TWSR & I2C_STATUS_MASK;
	return (status == I2C_DATA_SENT_ACK) ? I2C_OK : status;
}

uint8_t i2cReceive(uint8_t last, uint8_t * data)
{
	TWCR = last ? (1 << TWEN) | (1 << TWINT) : (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while(!(TWCR & (1 << TWINT)));
	*data = TWDR;
	uint8_t status = TWSR & I2C_STATUS_MASK;
	if(last)
		return (status == I2C_DATA_RECEIVED_NACK) ? I2C_OK : status;
	else
		return (status == I2C_DATA_RECEIVED_ACK) ? I2C_OK : status;
}

void i2cWriteRegister(uint8_t dev_address, uint8_t dev_register, uint8_t data)
{
	i2cStart();
	i2cSendAddress(dev_address << 1);
	i2cSendData(dev_register);
	i2cSendData(data);
	i2cStop();
}

void i2cReadRegister(uint8_t dev_address, uint8_t dev_register, uint8_t * data)
{
	i2cStart();
	i2cSendAddress(dev_address << 1);
	i2cSendData(dev_register);
	i2cStart();
	i2cSendAddress((dev_address << 1) & 0b00000001);
	i2cReceive(1, data);
	i2cStop();
}



