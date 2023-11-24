#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#define PhotoRes "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"

// Grabs voltage sample
double sampleInV() {
	FILE *voltage_file = fopen(PhotoRes, "r");
	if (!voltage_file) {
		printf("ERROR: Unable to open voltage input file\n");
		exit(-1);
	}
	int value = 0;
	fscanf(voltage_file, "%d", &value);
	fclose(voltage_file);
    double val = value;
	return val;
}

void * Sampler_startSampling(double buffer[]) {
    // fill array for 1s
    long long startTime = getTimeInMicroSeconds();
    printf("%llu ", startTime);
    long long currentTime = getTimeInMicroSeconds();
    int i = 0;
    
    while(currentTime < (startTime + 1000000)) {
        
        buffer[i] = sampleInV();
        sleepForMs(1);
        printf("%lf %d\n", buffer[i], i);
        i++;

        currentTime = getTimeInMicroSeconds();
        printf("%llu ", currentTime);
    }
    // printf("\n # of samples: %d", i);

    return NULL;
}

// void Sampler_stopSampling(void) {
    
// }
