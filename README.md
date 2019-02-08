# Robot arm

This is firmware for robotic arm based on ATMega32. It uses UART to get 
signals from computer containing servo posistion directives. Later it sends commands via I2C to 
PWM module.

It also drives LCD display to show latest signals received.
