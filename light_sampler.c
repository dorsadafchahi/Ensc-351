// Assignment 2 ENSC351
// Started November 16th, 2023
// Finished and submitted December 5th, 2023
// Code written by and contributed by:
// Nicholas H, Dorsa A, Lester P, Jim P.
// 
// This program will implement a light dip analyser
//
// Description of this program:
//  Sample from photoresistor ~500 times a second, and record times
//  Calculate values based on this data
//  Print this data to 8x8 LED matrix based on the joystick direction
//  Refresh this data every second
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
    // //initialize the GPIO USER BUTTON
    runCommand("config-pin p8.43 gpio");
    writetoFile("in");

    //initialize the LED MATRIX (TO DO)
    runCommand("config-pin P9_18 i2c");
    runCommand("config-pin P9_17 i2c");
    runCommand("i2cset -y 1 0x70 0x21 0x00");
    runCommand("i2cset -y 1 0x70 0x81 0x00");
    printf("Starting to sample data...\n");

    long long start_time = getTimeInMicroS();
    long long current_time = getTimeInMicroS();
    
    //run thread 1 to fill the struct
    pthread_create(&thread1, NULL, &Sampler_startSampling, NULL);
    sleepForMs(1);
    while(1){
        //every 1 second, the second thread will run again and again, printing output to the screen based on the struct values given from the first thread
        if (current_time > start_time + 1000000){
            //thread2 for calculations of the struct data
            pthread_create(&thread2, NULL, &Sampler_startAnalysis, NULL);
            start_time = getTimeInMicroS();
        }   
        //add a case if the user button is pressed, then exit program
        if (getGPIOvalue() == 48){// 48 = pressed
            printf("Shutting down...\n");
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
            pthread_cancel(thread1);
            pthread_cancel(thread2);
            Sampler_stopSampling();
            return 0;
        }
        current_time = getTimeInMicroS();
    }
    
    return 0;
}