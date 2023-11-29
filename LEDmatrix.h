#ifndef LEDmatrix_H
#define LEDmatrix_H

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <linux/i2c.h> 
#include <linux/i2c-dev.h> 

#define I2C_DEVICE_ADDRESS 0x20 

#define REG_DIRA 0x00 
#define REG_DIRB 0x01 
#define REG_OUTA 0x14 
#define REG_OUTB 0x15 

// Assume pins already configured for I2C: 
//   (bbg)$ config-pin P9_18 i2c 
//   (bbg)$ config-pin P9_17 i2c 
#define I2CDRV_LINUX_BUS0 "/dev/i2c-0" 
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1" 
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

static int initI2cBus(char* bus, int address);
static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);


#endif