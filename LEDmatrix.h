#ifndef LEDmatrix_H
#define LEDmatrix_H

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <linux/i2c.h> 
#include <linux/i2c-dev.h> 

#define I2C_DEVICE_ADDRESS 0x70 

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0" 
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1" 
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2" 

int initI2cBus(char* bus, int address);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char *value);

void displayInt(int number);
void displayDouble(double number);

#endif