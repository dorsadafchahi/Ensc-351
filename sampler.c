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
    double average_voltage = 0;
    // double min_voltage;
    // double max_voltage;
    // long long average_time = 0;
    // long long max_time;
    // long long min_time;
    int num_dips = 0;

    //lock the mutex for use
    pthread_mutex_lock(&mutexlock);
    //loop through entire buffer structure array
    for (int i = 0; i < buffer_index; i++){
        average_voltage = calculate_averageV(i, average_voltage);

        if (calculate_dip(i, average_voltage) == true){
            num_dips++;
        }
    }
    //reset the buffer_index to 0, to make the thread1 start from 0 filling the struct array
    buffer_index = 0;
    //unlock the mutex for use
    pthread_mutex_unlock(&mutexlock);
    //printf("Interval ms (0.000, 3.058) avg=1.825   Samples V (1.289, 1.300) avg=1.124   # Dips:   0   # Samples:    547\n");
    return NULL;
}

//function to calculate the average of the voltages so far
double calculate_averageV(int index, double current_avg){
    double new_avg;
    double before_total = current_avg*(index-1);
    double new_total = before_total + buffer[index].sampleInV;
    new_avg = new_total/index;
    return new_avg;
}

//function to calculate if a voltage dip or not, current voltage average needed to compare
bool calculate_dip(int index, double average){
    //a dip is detected if the voltage is 0.1V or more away from curent average
    //but, if the difference from the previous V and current V is less than 0.03V difference, 
    // then it is classified not a dip
    if (abs(buffer[index-1].sampleInV - buffer[index].sampleInV) < 0.03){
        return false;
    }    
    else if (abs(average - buffer[index].sampleInV) >= 0.1){
        return true;
    }
    else{
        return false;
    }
}

//function to end
void Sampler_stopSampling() {
    pthread_mutex_destroy(&mutexlock);
    free(buffer);    
}
