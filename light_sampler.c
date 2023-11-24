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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mini_main.c"
#include "joystick.h"
#include "sampler.h" // sampler.h #includes time.h

#define GPIO_EXPORT "/sys/class/gpio/export"
#define USER_BUTTON_VALUE "/sys/class/gpio/gpio72/value"
#define USER_BUTTON_DIRECTION  "/sys/class/gpio/gpio72/direction"

// static char getGPIOvalue(char* file_name);
// double voltage_file_read(char* file_name);
// static void runCommand(char* command);
// static void writetoFile(const char* fileName, const char* value);

int main(int argc, char* args[])
{
    printf("hello world!\n\n");

    mini_main();

    // runCommand("cd /sys/class/gpio");
    // runCommand("config-pin p8.43 gpio");
    // writetoFile(USER_BUTTON_DIRECTION, "in");

    // double Xval = Joystick_readX();
    // double Yval = Joystick_readY();
    // double photo_val = voltage_file_read(PhotoRes);
    
    // printf("USER button value is  : %d\n", getGPIOvalue(USER_BUTTON_VALUE));
    // printf("X-val is              : %f\n", Xval);
    // printf("Y-val is              : %f\n", Yval);
    // printf("Photoresistor -val is : %f\n", photo_val);

    return 0;
}

//function to get value of a GPIO file
// static char getGPIOvalue(char* file_name){
//     FILE *file = fopen(file_name, "r");
//     if (file == NULL){
//         printf("Error opening file %s\n", file_name);
//         exit(1);
//     }
//     int value = fgetc(file);
//     fclose(file);
//     return value;
// }


//given function to run a linux command in C
// static void runCommand(char* command) {    
//     // Execute the shell command (output into pipe)    
//     FILE *pipe = popen(command, "r");    
//     // Ignore output of the command; but consume it     
//     // so we don't get an error when closing the pipe.    
//     char buffer[1024];    
//     while (!feof(pipe) && !ferror(pipe)) {        
//         if (fgets(buffer, sizeof(buffer), pipe) == NULL)            
//         break;        
//         // printf("--> %s", buffer);  // Uncomment for debugging    
//     }    
//     // Get the exit code from the pipe; non-zero is an error:    
//     int exitCode = WEXITSTATUS(pclose(pipe));    
//     if (exitCode != 0) {        
//         perror("Unable to execute command:");        
//         printf("  command:   %s\n", command);        
//         printf("  exit code: %d\n", exitCode);    
//     } 
// }

//function to write to file
// static void writetoFile(const char* fileName, const char* value){
// 	FILE *pFile = fopen(fileName, "w");
//     if (pFile == NULL) {
//         printf("ERROR: Unable to open file %s.\n", fileName);
//         exit(1);
//     }
// 	fprintf(pFile, "%s", value);
// 	fclose(pFile);
// }

