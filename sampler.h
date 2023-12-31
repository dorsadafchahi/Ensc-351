// sampler.h
// Module to sample light levels in the background (thread).
// It provides access to the raw samples and then deletes them.
#ifndef SAMPLER_H
#define SAMPLER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "LEDmatrix.h"
#include "joystick.h"

#define PhotoRes "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"

typedef struct {
    double sampleInV;
    long long getTimeInMicroSeconds;
} samplerDatapoint_t;

//function to get voltage reading from photoresistor
double sampleInVolts();

// Begin/end the background thread which samples light levels.
void *Sampler_startSampling();
void Sampler_stopSampling();

//thead function to run in tandem with start sampling, that, with the help of mutexes, will analyze the array after it is filled
void *Sampler_startAnalysis();

//convert the 4095 number to voltage
double convertToVoltage(double number);

//functions to calculate analysis on the data accumulated in the structured array
double calculate_averageV(int index, double current_avg);
bool calculate_dip(int index, double average);
long long calculate_averageT(long long time_interval, long long current_avg);


#endif