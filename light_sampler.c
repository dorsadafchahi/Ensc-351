//This program will implement a light dip analyser
//Assignment 2 ENSC351
//Code written by and contributed by:
//Nicholas H, Dorsa, Lester, Jim P.
//
//Description of this program:
//  Sample from photoresistor ~500 times a second
//  other stuff
//  Print this data to 8x8 LED matrix
//  Exit program from pressing USER/BOOT button

#include "joystick.h"
#include "sampler.h" // sampler.h #includes time.h
#include "button.h"
#include "time.h"
#include "LEDmatrix.h"

//variables for the 2 threads
pthread_t thread1;
pthread_t thread2;

int main(int argc, char* args[])
{
    printf("Starting to sample data...\n");

    runCommand("config-pin P9_18 i2c");
    runCommand("config-pin P9_17 i2c");
    //runCommand("i2cset -y 1 0x70 0x81 0x00");
   
    //                          "/dev/i2c-1"        0x70
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); 
    writeI2cReg(i2cFileDesc, REG_DIRA, 0x00); 
    writeI2cReg(i2cFileDesc, REG_DIRB, 0x00); 
       
    // // Drive an hour-glass looking character 
    // // (Like an X with a bar on top & bottom) 
    writeI2cReg(i2cFileDesc, REG_OUTA, 0x2A); 
    writeI2cReg(i2cFileDesc, REG_OUTB, 0x54); 
    
    // // Read a register: 
    // unsigned char regVal = readI2cReg(i2cFileDesc, REG_OUTA); 
    // printf("Reg OUT-A = 0x%02x\n", regVal); 

    // Cleanup I2C access; 
    close(i2cFileDesc); 

    // //initialize the GPIO USER BUTTON
    // runCommand("config-pin p8.43 gpio");
    // writetoFile("in");

    // //initialize the LED MATRIX (TO DO)
    // //initialize_led_matrix()

    // long long start_time = getTimeInMicroS();
    // long long current_time = getTimeInMicroS();
    
    // //run thread 1 to fill the struct
    // pthread_create(&thread1, NULL, &Sampler_startSampling, NULL);
    // // sleepForMs(1);
    // while(1){
    //     //every 1 second, the second thread will run again and again, printing output to the screen based on the struct values given from the first thread
    //     if (current_time > start_time + 1000000){
    //         //thread2 for calculations of the struct data
    //         pthread_create(&thread2, NULL, &Sampler_startAnalysis, NULL);
    //         start_time = getTimeInMicroS();
    //     }   
    //     //add a case if the user button is pressed, then exit program
    //     if (getGPIOvalue() == 48){// 48 = pressed
    //         printf("Shutting down...\n");
    //         pthread_join(thread1, NULL);
    //         pthread_join(thread2, NULL);
    //         pthread_cancel(thread1);
    //         pthread_cancel(thread2);
    //         Sampler_stopSampling();
    //         return 0;
    //     }
    //     current_time = getTimeInMicroS();
    // }
    
    return 0;
}