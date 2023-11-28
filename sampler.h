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
#define PhotoRes "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"


typedef struct {
    double sampleInV;
    long long getTimeInMicroSeconds;
} samplerDatapoint_t;

// Begin/end the background thread which samples light levels.
void *Sampler_startSampling();
void Sampler_stopSampling();

//thead function to run in tandem with start sampling, that, with the help of mutexes, will analyze the array after it is filled
void *Sampler_startAnalysis();

// Get a copy of the samples in the sample history, removing values
// from our history here.
// Returns a newly allocated array and sets `length` to be the
// number of elements in the returned array (output-only parameter).
// The calling code must call free() on the returned pointer.
// Note: function provides both data and size to ensure consistency.
samplerDatapoint_t* Sampler_extractAllValues(int *length);

// Returns how many valid samples are currently in the history.
int Sampler_getNumSamplesInHistory();

// Get the total number of light level samples taken so far.
long long Sampler_getNumSamplesTaken(void);

#endif