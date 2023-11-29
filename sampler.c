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
    
    //start sampling here
    while(1){
        int value;
        // double voltage;
        value = sampleInVolts();
        // voltage = convertToVoltage(value);

        //this should only happen if thread2 is gonna stop, eg the button was pressed
        if(buffer_index > 900){
            printf("Done shutdown! Goodbye!\n");
            return NULL;
        }

        //lock the mutex
        pthread_mutex_lock(&mutexlock);

        //store values in the struct
        buffer[buffer_index].sampleInV = value;
        buffer[buffer_index].getTimeInMicroSeconds = getTimeInMicroS();
        buffer_index++;

        //unlock the mutex, for the second thread to gain access if need be
        pthread_mutex_unlock(&mutexlock);

        sleepForMs(1.5);
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

    //lock the mutex for use
    pthread_mutex_lock(&mutexlock);
    //ALL CALCULATIONS HERE WITH
    //buffer[buffer_index2].sampleInV
    //buffer[buffer_index2].timestampInNanoS
    //buffer_index++;

    printf("samples in buffer: %d\n", buffer_index);
    //reset the buffer_index to 0, to make the thread1 start from 0 filling the struct array
    buffer_index = 0;
    pthread_mutex_unlock(&mutexlock);
    //printf("Interval ms (0.000, 3.058) avg=1.825   Samples V (1.289, 1.300) avg=1.124   # Dips:   0   # Samples:    547\n");
    return NULL;
}

void Sampler_stopSampling() {
    pthread_mutex_destroy(&mutexlock);
    free(buffer);    
}
