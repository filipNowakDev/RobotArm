/*
 * kbd.h
 *
 * Created: 16.09.2018 11:45:30
 *  Author: Filip
 */ 


#ifndef KBD_H_
#define KBD_H_
#include <avr/io.h>


#define KBD_PORT PORTB
#define KBD_DDR DDRB
#define KBD_PIN PINB
//rows --> pins 0 - 3 
//columns --> pins 4 - 7

void initKeyboard();
uint8_t readKeyboard();



#endif /* KBD_H_ */