/*
 * LCD_lib.c
 *
 * Created: 14.09.2018 20:46:49
 * Author : Filip
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

static uint8_t switchedTo4BitMode;
static uint8_t checkBusyFlag;


void lcdWrite(uint8_t data, uint8_t rs, uint8_t checkBusyFlag)
{
	if (checkBusyFlag)
	{
		while(lcdReadAddress() & 0b10000000)
			_delay_us(20);
	}
	
	LCD_RW_LOW;
	if(rs)
		LCD_RS_HIGH;
	else
		LCD_RS_LOW;
		
	#ifdef BITS4
		LCD_DATA_DDR |= 0xF0;
		
		LCD_DATA_PORT &= data | 0x0F;
		LCD_DATA_PORT |= data & 0xF0;
		
	#else
		LCD_DATA_DDR = 0xFF;
		
		LCD_DATA_PORT = data;
	#endif
	
	LCD_E_HIGH;
	_delay_us(1);
	LCD_E_LOW;
	_delay_us(1);
	
}

uint8_t lcdRead(uint8_t rs, uint8_t checkBusyFlag)
{
	if (checkBusyFlag)
	{
		while(lcdReadAddress() & 0b10000000)
			asm("NOP");
	}
	
	LCD_RW_HIGH;
	if(rs)
		LCD_RS_HIGH;
	else
		LCD_RS_LOW;
		
	#ifdef BITS4
		LCD_DATA_DDR &= 0x0F;
	#else
		LCD_DATA_DDR = 0x00;
	#endif
	
	LCD_E_HIGH;
	_delay_us(1);
	uint8_t data = LCD_DATA_INPUT;
	LCD_E_LOW;
	_delay_us(1);
	return data;
}

uint8_t lcdReadAddress()
{
	if(switchedTo4BitMode)
		return ((lcdRead(0, 0) & 0xF0) | (lcdRead(0, 0) >> 4));
	else
		return lcdRead(0, 0);
}

uint8_t lcdReadData()
{
	if(switchedTo4BitMode)
		return ((lcdRead(1, 1) & 0xF0) | (lcdRead(1, 0) >> 4));
	else
		return lcdRead(1, checkBusyFlag);
}

void lcdWriteCommand(uint8_t command)
{
	if (switchedTo4BitMode)
	{
		lcdWrite(command, 0, 1);
		lcdWrite(command << 4, 0, 0);
	}
	else
		lcdWrite(command, 0, 1);
}

void lcdWriteData(uint8_t data)
{
	if (switchedTo4BitMode)
	{
		lcdWrite(data, 1, 1);
		lcdWrite(data << 4, 1, 0);
	}
	else
	lcdWrite(data, 1, checkBusyFlag);
}

void lcdWriteString(char* string)
{
	uint8_t i = 0;
	while(string[i] != '\0')
		lcdWriteData(string[i++]);
}

void lcdGoToXY(uint8_t x, uint8_t y)
{
	lcdWriteCommand(LCD_COMMAND_SET_DDRAM_ADDRESS | (x + y * 0x40));
}

void lcdClear()
{
	lcdWriteCommand(LCD_COMMAND_CLEAR);
}

int put(char c, FILE* file)
{
	lcdWriteData(c);
	return 0;
}

void lcdInitPrintf()
{
	fdevopen(put, NULL);
}

void lcdInit()
{
	switchedTo4BitMode = 0;
	checkBusyFlag = 0;
	LCD_E_DDR |= (1 << LCD_E_PIN);
	LCD_RW_DDR |= (1 << LCD_RW_PIN);
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	_delay_ms(15);
	lcdWriteCommand(LCD_COMMAND_FUNCTION_SET | LCD_PARAM_FUNCTION_SET_8BIT);
	_delay_ms(4.1);
	lcdWriteCommand(LCD_COMMAND_FUNCTION_SET | LCD_PARAM_FUNCTION_SET_8BIT);
	_delay_ms(0.1);
	lcdWriteCommand(LCD_COMMAND_FUNCTION_SET | LCD_PARAM_FUNCTION_SET_8BIT);

	#ifdef BITS4
		_delay_ms(1);
		lcdWriteCommand(LCD_COMMAND_FUNCTION_SET);
		_delay_ms(1);
		switchedTo4BitMode = 1;
		checkBusyFlag = 1;
		lcdWriteCommand(LCD_COMMAND_FUNCTION_SET | LCD_PARAM_FUNCTION_SET_2LINES);
	#else
		checkBusyFlag = 1;
		lcdWriteCommand(LCD_COMMAND_FUNCTION_SET | LCD_PARAM_FUNCTION_SET_8BIT | LCD_PARAM_FUNCTION_SET_2LINES);
	#endif
	lcdWriteCommand(LCD_COMMAND_ON_OFF);
	lcdWriteCommand(LCD_COMMAND_ON_OFF | LCD_PARAM_ON_OFF_DISPLAY);
	lcdWriteCommand(LCD_COMMAND_ENTRY_MODE_SET | LCD_PARAM_ENTRY_MODE_SET_INCREMENT);
	lcdWriteCommand(LCD_COMMAND_CLEAR);
		
	
}
