#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define JoyX "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define JoyY "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

double Joystick_readX();
double Joystick_readY();
int getDirection();

#endif