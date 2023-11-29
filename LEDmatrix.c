#include "LEDmatrix.h"

static int initI2cBus(char* bus, int address) 
{ 
    int i2cFileDesc = open(bus, O_RDWR); 
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address); 
    if (result < 0) { 
        perror("I2C: Unable to set I2C device to slave address."); 
        exit(1); 
    } 
    return i2cFileDesc; 
}

static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value) 
{ 
    unsigned char buff[2]; 
    buff[0] = regAddr; 
    buff[1] = value; 
    int res = write(i2cFileDesc, buff, 2); 
    if (res != 2) { 
        perror("I2C: Unable to write i2c register."); 
        exit(1); 
    }
}

static unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr) 
{ 
    // To read a register, must first write the address 
    int res = write(i2cFileDesc, &regAddr, sizeof(regAddr)); 
    if (res != sizeof(regAddr)) { 
        perror("I2C: Unable to write to i2c register."); 
        exit(1); 
    } 
        
    // Now read the value and return it 
    char value = 0; 
    res = read(i2cFileDesc, &value, sizeof(value)); 
    if (res != sizeof(value)) { 
        perror("I2C: Unable to read from i2c register"); 
        exit(1); 
    } 
    return value; 
}

int main() 
{ 
    printf("Drive display (assumes GPIO #61 and #44 are output and 1\n"); 
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); 
    writeI2cReg(i2cFileDesc, REG_DIRA, 0x00); 
    writeI2cReg(i2cFileDesc, REG_DIRB, 0x00); 
    
    // Drive an hour-glass looking character 
    // (Like an X with a bar on top & bottom) 
    writeI2cReg(i2cFileDesc, REG_OUTA, 0x2A); 
    writeI2cReg(i2cFileDesc, REG_OUTB, 0x54); 
    
    // Read a register: 
    unsigned char regVal = readI2cReg(i2cFileDesc, REG_OUTA); 
    printf("Reg OUT-A = 0x%02x\n", regVal); 
    
    // Cleanup I2C access; 
    close(i2cFileDesc); 
    return 0; 
}