/*
 * lcd.h
 *
 * Created: 14.09.2018 20:47:49
 *  Author: Filip
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>

#define LCD_E_PIN PORTA0
#define LCD_RW_PIN PORTA1
#define LCD_RS_PIN PORTA2

#define LCD_E_PORT PORTA
#define LCD_RW_PORT PORTA
#define LCD_RS_PORT PORTA

#define LCD_E_DDR DDRA
#define LCD_RW_DDR DDRA
#define LCD_RS_DDR DDRA


#define LCD_E_LOW LCD_E_PORT &= ~(1 << LCD_E_PIN)
#define LCD_RW_LOW LCD_RW_PORT &= ~(1 << LCD_RW_PIN)
#define LCD_RS_LOW LCD_RS_PORT &= ~(1 << LCD_RS_PIN)

#define LCD_E_HIGH LCD_E_PORT |= (1 << LCD_E_PIN)
#define LCD_RW_HIGH LCD_RW_PORT |= (1 << LCD_RW_PIN)
#define LCD_RS_HIGH LCD_RS_PORT |= (1 << LCD_RS_PIN)

#define LCD_DATA_PORT PORTA
#define LCD_DATA_INPUT PINA
#define LCD_DATA_DDR DDRA

//comment below line to turn on 8 bit operation
#define BITS4

void lcdWrite(uint8_t data, uint8_t rs, uint8_t checkBusyFlag);
uint8_t lcdRead(uint8_t rs, uint8_t checkBusyFlag);
uint8_t lcdReadAddress();
uint8_t lcdReadData();
void lcdWriteCommand(uint8_t command);
void lcdWriteData(uint8_t data);
void lcdWriteString(char* string);
void lcdGoToXY(uint8_t x, uint8_t y);
void lcdClear();
int put(char c, FILE* file);
void lcdInitPrintf();
void lcdInit();
#define LCD_COMMAND_CLEAR 0x01
#define LCD_COMAND_RETURN_HOME 0x02
#define LCD_COMMAND_ENTRY_MODE_SET 0x04
#define LCD_COMMAND_ON_OFF 0x08
#define LCD_COMMAND_SHIFT 0x10
#define LCD_COMMAND_FUNCTION_SET 0x20
#define LCD_COMMAND_SET_CGRAM_ADDRESS 0x40
#define LCD_COMMAND_SET_DDRAM_ADDRESS 0x80

#define LCD_PARAM_ENTRY_MODE_SET_SHIFT 0x01
#define LCD_PARAM_ENTRY_MODE_SET_INCREMENT 0x02
#define LCD_PARAM_ON_OFF_BLINK 0x01
#define LCD_PARAM_ON_OFF_CURSOR 0X02
#define LCD_PARAM_ON_OFF_DISPLAY 0x04
#define LCD_PARAM_SHIFT_RIGHT 0x04
#define LCD_PARAM_SHIFT_DISPLAY 0x08
#define LCD_PARAM_FUNCTION_SET_5X10 0x04
#define LCD_PARAM_FUNCTION_SET_2LINES 0x08
#define LCD_PARAM_FUNCTION_SET_8BIT 0x10


#endif /* LCD_H_ */