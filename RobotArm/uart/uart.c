/*
 * uart.c
 *
 * Created: 22.09.2018 15:05:37
 *  Author: Filip
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

void initUart()
{
	UBRRH = (uint8_t) (UBRR_VAL >> 8);
	UBRRL = (uint8_t) (UBRR_VAL);
	#ifdef DOUBLE_BAUD
		UCSRA |= (1 << U2X);
	#endif
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void uartTransmit(uint8_t data)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t uartReceive()
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}

void uartTransmitString(char* str)
{
	uint8_t cnt = 0;
	while(str[cnt] != '\0')
	{
		uartTransmit(str[cnt++]);
	}
}

uint16_t uartReceiveIntAsChars(uint8_t width)
{
	char num[6];
	for (int i = 0; i < width; i++)
	{
		num[i] = uartReceive();
	}
	num[width] = '\0';
	return atoi(num);
}

uint16_t uartReceiveUint16Binary()
{
	uint8_t byte_high = uartReceive();
	return (byte_high << 8) & uartReceive();
}

void uartTransmitUint16Binary(uint16_t data)
{
	uint8_t byte_high = data >> 8;
	uartTransmit(byte_high);
	uartTransmit((uint8_t)(data));
}
