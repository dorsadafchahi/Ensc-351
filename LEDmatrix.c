#include "LEDmatrix.h"

char zero[] = {};
char one[] = {};
char two[] = {};
char three[] = {};
char four[] = {};
char five[] = {};
char six[] = {};
char seven[] = {};
char eight[] = {};
char nine[] = {};

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

char intToBinary(int number){
    switch (number) {
    case 0:
        return zero;
        break;
    case 1:
        return one;
        break;
    case 2:
        return two;
        break;
    case 3:
        return three;
        break;
    case 4:
        return four;
        break;
    case 5:
        return five;
        break;
    case 6:
        return six;
        break;
    case 7:
        return seven;
        break;
    case 8:
        return eight;
        break;
    case 9:
        return nine;
        break;
    }
    printf("error.\n");
    return NULL;
}

void displayInt(int number){
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

    char LEDdisplay[7];
    int num1;
    int num2;

    //single digit number (eg 07, 09, 00)
    if (number < 10){
        num1 = 0;
        //check if number is equal or lower than 0
        if (number <= 0){
            num2 = 0;
        }
        else{
            num2 = number % 10; //found on stack overflow
        }
    }
    //double digit number (eg 10, 48, 92)
    else if (number <= 99){
        num1 = (number / 10) % 10;
        num2 = number % 10;
    }
    //if number is bigger than 99, then set number to 99
    else if (number > 99){
        num1 = 9;
        num2 = 9;
    }

    //convert the num1 and num2 to binary for LED display described at top of file
    char number1 = intToBinary(num1);
    char number2 = intToBinary(num2);

    for (int i = 0; i < 8; i++){
        char bothnums = number1[i] << 4 | number2[i];
        LEDdisplay[i] = bothnums;
    }

    writeI2cReg
}