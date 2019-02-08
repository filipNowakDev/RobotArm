/*
 * uart.h
 *
 * Created: 22.09.2018 15:05:28
 *  Author: Filip
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 1000000
#define BAUD 4800
//comment lower line to turn off u2x
#define DOUBLE_BAUD
#define UBRR_VAL (F_CPU/16/BAUD-1)

void initUart();
void uartTransmit(uint8_t data);
uint8_t uartReceive();
void uartTransmitString(char* str);
uint16_t uartReceiveIntAsChars(uint8_t width);
uint16_t uartReceiveUint16Binary();
void uartTransmitUint16Binary(uint16_t data);
#endif /* UART_H_ */