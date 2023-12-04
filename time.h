#ifndef TIME_H
#define TIME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Get current time function
long long getTimeInMicroS(void);

// Add delay (in number of milliseconds)
void sleepForMs(long long delayInMs);

// Convert Microseconds to milliseconds
double displayMicroToMs(long long val);

#endif