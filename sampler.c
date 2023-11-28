#include "sampler.h"

//variable for buffer struct with values and timestamps
samplerDatapoint_t* buffer;
//index for the buffer array
int buffer_index;

//variables mutex lock within both threads
pthread_mutex_t mutexlock;

// Grabs voltage sample
double sampleInVolts() {
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

void *Sampler_startSampling() {
    // printf("starting thread1\n");
    
    //initialize array
    buffer_index = 0;

    buffer = (samplerDatapoint_t *)malloc(1000 * sizeof(samplerDatapoint_t));
    if (buffer == NULL){
        printf("error: memory not allocated properly\n");
        exit(-1);
    }
    if (pthread_mutex_init(&mutexlock, NULL) != 0){
        printf("mutex lock initialization failed\n");
        exit(-1);
    }
        // printf("test\n");

    //start sampling here
    while(1){
        int value;
        // double voltage;
        value = sampleInVolts();
        // voltage = convertToVoltage(value);
        //this should never happen
        if(buffer_index > 900){
            printf("Error, buffer index too high\n");
            exit(-1);
        }
        // printf("> test whileloop\n");

        //lock the mutex
        pthread_mutex_lock(&mutexlock);
        // printf("test lock\n");

        //store values in the struct
        buffer[buffer_index].sampleInV = value;
        buffer[buffer_index].getTimeInMicroSeconds = getTimeInMicroS();
        buffer_index++;
        //unlock the mutex, for the second thread to gain access
        pthread_mutex_unlock(&mutexlock);
        // printf("test unlock\n");

        sleepForMs(5);
    }
    return NULL;
}

void *Sampler_startAnalysis() {
    // int buffer_index = 0;
    //these are all the values we will calculate in this function for printf at the end
    // double average_voltage;
    // double min_voltage;
    // double max_voltage;
    // long long average_time;
    // long long max_time;
    // long long min_time;
    //int num_dips();
    printf("starting thread2\n");
    int i;
    //lock the mutex for use
    pthread_mutex_lock(&mutexlock);
    //ALL CALCULATIONS HERE WITH
    //buffer[buffer_index2].sampleInV
    //buffer[buffer_index2].timestampInNanoS
    //buffer_index++;
    printf("test ---------------------\n");
    for(i = 0; i < buffer_index; i++) {
        printf("buffer: %f\n", buffer[i].sampleInV);
    }
    printf("samples in buffer: %d\n\n\n", i);
    buffer_index = 0;
    pthread_mutex_unlock(&mutexlock);
    printf("Interval ms (0.000, 3.058) avg=1.825   Samples V (1.289, 1.300) avg=1.124   # Dips:   0   # Samples:    547\n");
    // sleepForMs(10);
    return NULL;
}

void Sampler_stopSampling() {
    pthread_mutex_destroy(&mutexlock);
    free(buffer);    
}
