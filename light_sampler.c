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

//variables for the 2 threads
pthread_t thread1;
pthread_t thread2;

int main(int argc, char* args[])
{
    printf("hello world!\n\n");


    //initialize the GPIO USER BUTTON
    runCommand("config-pin p8.43 gpio");
    writetoFile("in");

    //initialize the LED MATRIX (TO DO)
    //initialize_led_matrix()

    long long start_time = getTimeInMicroS();
    long long current_time = getTimeInMicroS();
    int i = 0;
    int it = 0;
    //run thread 1 to fill the struct
    pthread_create(&thread1, NULL, &Sampler_startSampling, NULL);
    // sleepForMs(1);
    while(1){
        //every 1 second, the second thread will run again and again, printing output to the screen based on the struct values given from the first thread
        if (current_time > start_time + 1000000){
            pthread_create(&thread2, NULL, &Sampler_startAnalysis, NULL);//thread2 for calculations of the struct data
            start_time = getTimeInMicroS();
            printf("thread_analysis: %d\n", it);
            it++;

        }   
        //add a case if the user button is pressed, then exit program
        if (getGPIOvalue() == 48){// 48 = pressed
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
            pthread_cancel(thread1);
            pthread_cancel(thread2);
            Sampler_stopSampling();
        }
        // printf("run: %d\n", i);
        i++;
        current_time = getTimeInMicroS();
    }
    return 0;
}