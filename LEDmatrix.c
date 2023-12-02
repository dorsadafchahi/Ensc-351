#include "LEDmatrix.h"

char zero[] =   {7, 5, 5, 5, 5, 5, 7};// each of these numbers represent a lint on the 8x8 LED matrix, in binary so 7 would be ..., 5 would be . .
char one[] =    {3, 2, 2, 2, 2, 2, 7};
char two[] =    {7, 4, 4, 7, 1, 1, 7};
char three[] =  {7, 4, 4, 7, 4, 4, 7};
char four[] =   {5, 5, 5, 7, 4, 4, 4};
char five[] =   {7, 1, 1, 7, 4, 4, 7};
char six[] =    {7, 1, 1, 7, 5, 5, 7};
char seven[] =  {7, 4, 4, 4, 4, 4, 4};
char eight[] =  {7, 5, 5, 7, 5, 5, 7};
char nine[] =   {7, 5, 5, 7, 4, 4, 4};
char decimal =  8;

int initI2cBus(char* bus, int address) 
{ 
    int i2cFileDesc = open(bus, O_RDWR); 
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address); 
    if (result < 0) { 
        perror("I2C: Unable to set I2C device to slave address."); 
        exit(1); 
    } 
    return i2cFileDesc; 
}

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char *value) 
{ 
    unsigned char buff[17]; 
    buff[0] = regAddr; 
    int i2 = 1;
    for (int i = 0; i < 8; i++){
        buff[i2] = value[i];
        i2 = i2 + 2;
    }
    int res = write(i2cFileDesc, buff, 17); 
    if (res != 17) { 
        perror("I2C: Unable to write i2c register."); 
        exit(1); 
    }
}

char *intToBinary(int number){
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

    unsigned char LEDdisplay[8];
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
    char *number1 = intToBinary(num1);
    char *number2 = intToBinary(num2);

    for (int i = 0; i < 8; i++){
        char bothnums = (number2[i] << 4) + number1[i];
        LEDdisplay[i] = bothnums;
    }
    LEDdisplay[7] = 0;
    writeI2cReg(i2cFileDesc, 0x00, LEDdisplay); 

    close(i2cFileDesc); 
}

void displayDouble(double number) {
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
    
    unsigned char LEDdisplay[8];
    int num1;
    int num2;

    int number10 = number * 10;
        //single digit number (eg 07, 09, 00)
    if (number10 < 10){
        num1 = 0;
        //check if number is equal or lower than 0
        if (number10 <= 0){
            num2 = 0;
        }
        else{
            num2 = number10 % 10; //found on stack overflow
        }
    }
    //double digit number (eg 10, 48, 92)
    else if (number10 <= 99){
        num1 = (number10 / 10) % 10;
        num2 = number10 % 10;
    }
    //if number is bigger than 99, then set number to 99
    else if (number10 > 99){
        num1 = 9;
        num2 = 9;
    }

    //convert the num1 and num2 to binary for LED display described at top of file
    char *number1 = intToBinary(num1);
    char *number2 = intToBinary(num2);

    for (int i = 0; i < 8; i++){
        char bothnums = (number2[i] << 4) + number1[i];
        LEDdisplay[i] = bothnums;
    }
    LEDdisplay[7] = 8;
    writeI2cReg(i2cFileDesc, 0x00, LEDdisplay); 

    close(i2cFileDesc); 
}