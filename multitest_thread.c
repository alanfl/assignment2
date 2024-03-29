//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

// This constant defines the maximum interval that any thread must iterate when performing its search
int THREAD_INTERVAL = 0;

typedef struct params_t {
    int start;
    int target_value;
    int length;
    int * array;
    int return_value;
} params_t;

// Usage: main search function, establishes threads dynamically and iterates through return values
int search(int * array, int length, int target_value);

// Usage: sets the interval size for each thread to iterate through
void set_interval(int interval);

// Usage: performs a linear search on an array within the specified interval
void * linear_search_thread(void * parameters);

// Usage: returns the mode of implementation
char * get_mode();

int search(int * array, int length, int target_value) {

    int index = -1;

    // Compute number of threads to run
    int num_threads = length / THREAD_INTERVAL + 1;

    // Generate array to store threads
    pthread_t threads[num_threads];
    // Params for each thread;
    params_t * parameters = malloc(num_threads * sizeof(params_t));

    for(int i = 0; i < num_threads; i++) {
        // Generate parameter structs dynamically
        parameters[i].start = i * THREAD_INTERVAL;
        parameters[i].target_value = target_value;
        parameters[i].length = length;
        parameters[i].array = array;
        parameters[i].return_value = -1;

        pthread_create( &threads[i], NULL, linear_search_thread, (void *) &parameters[i]);

        // Thread creation errored, report
        if(threads[i] == 0) {
            exit(-1);
        }
    }

    // Await threads to complete
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);

        // Check return value on returned threads
        if(parameters[i].return_value != -1) {
            index = parameters[i].return_value;
        }
    }

    // Return index if target_value was found, otherwise -1
    return index;
}

void set_interval(int interval) {
    THREAD_INTERVAL = interval;
}

void * linear_search_thread(void * parameters) {
    params_t * params = (params_t *) parameters;
    int start = params->start;

    // If this is the last interval, ensure that we don't check past the end of the array
    int end = start + THREAD_INTERVAL > params->length ? params->length : start + THREAD_INTERVAL;

    int * array = params->array;

    // Iterate through interval
    for(int i = start; i < end; i++) {
        if(array[i] == params->target_value) {
            params->return_value = i;
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}

char * get_mode() {
    return "mode: multi-thread";
}