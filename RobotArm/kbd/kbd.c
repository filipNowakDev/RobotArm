/*
 * kbd.c
 *
 * Created: 16.09.2018 11:45:15
 *  Author: Filip
 */ 

#include "kbd.h"
#include <util/delay.h>

void initKeyboard()
{
	KBD_DDR = 0x0F;	
}

uint8_t readKeyboard()
{
	for(uint8_t row = 0; row < 4; row++)
	{
		KBD_PORT = ~(1 << row);
		_delay_us(1);
		for(uint8_t col = 0; col < 4; col++)
		{
			if (~KBD_PIN & (1 << (col + 4)))
				return row * 4 + col + 1;
		}
	}
	return 0;
}
