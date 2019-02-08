/*
 * PCA9685_servo.h
 *
 * Created: 19.09.2018 20:42:09
 *  Author: Filip
 */ 


#ifndef PCA9685_SERVO_H_
#define PCA9685_SERVO_H_
#include <avr/io.h>


#define PCA9685_I2C_ADDR 0x40
#define PCA9685_MODE1 0x00
#define PCA9685_PRE_SCALE 0xFE

void initServosI2C();
void setServoPWM(uint8_t servo, uint16_t duty);




#endif /* PCA9685_SERVO_H_ */