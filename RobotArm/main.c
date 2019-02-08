/*
 * RobotArm.c
 *
 * Created: 22.09.2018 23:09:39
 * Author : Filip
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "uart/uart.h"
#include "lcd/lcd.h"
#include "i2c/i2c.h"
#include "servos/PCA9685_servo.h"

int main(void)
{
	i2cInit();
	initServosI2C();
	initUart();
	lcdInit();
	lcdInitPrintf();
	uint8_t init_val = uartReceive();
	while(init_val != 'i')
		init_val = uartReceive();
	uartTransmitString("READY");
	lcdClear();
	printf("READY");
    while (1)
    {
		//uint16_t servo = uartReceiveIntAsChars(1);
		//uint16_t duty = uartReceiveIntAsChars(3);
		//setServoPWM(servo, duty);
		//lcdClear();
		//printf("Servo %u:%u", servo, duty);
		uint8_t command = uartReceive();
		if(command == 's')
		{
			uint16_t servo = 0;
			servo = uartReceiveIntAsChars(1);
			if(uartReceive() == '.')
			{
				uint16_t duty = 0;
				duty = uartReceiveIntAsChars(3);
				if(uartReceive() != '.')
				{
					lcdClear();
					printf("duty error");
				}
				else
				{
					lcdGoToXY(0,0);
					setServoPWM(servo, duty);
					printf("Servo %u:%u", servo, duty);
				}
			}
			else
			{
				lcdClear();
				printf("servo error");
			}
		}
    }
}

