#ifndef TIME_H
#define TIME_H
#include "time.c"

// Get current time function
static long long getTimeInMicroSeconds(void);

// Add delay (in number of milliseconds)
static void sleepForMs(long long delayInMs);

#endif