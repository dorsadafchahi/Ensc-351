#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "sampler.h"

int mini_main() {

    double buff[1000];

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, Sampler_startSampling(buff), NULL);
    pthread_join(thread_id, NULL);

    return 0;

    // Sampler_stopSampling(void);
    
}