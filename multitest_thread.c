//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include <stdlib.h>
#include <pthread.h>

// This constant defines the maximum interval that any thread must iterate when performing its search
const int THREAD_INTERVAL = 250;

typedef struct params_t {
    int start;
    int target_value;
    int length;
    int * array;
} params_t;

int search(int * array, int length, int target_value);

// Usage: performs a linear search on an array within the specified interval
void * linear_search_thread(void * parameters);

char * get_mode();

int search(int * array, int length, int target_value) {

    int index = -1;

    // Compute number of threads to run
    int num_threads = length / THREAD_INTERVAL;

    // Generate array to store threads
    pthread_t threads[num_threads];
    int return_values[num_threads];
    // params_t * params[num_threads];

    for(int i = 0; i < num_threads; i++) {
        pthread_t thread_handle;

        // Generate parameter structs dynamically
        params_t * parameters = malloc(sizeof(params_t));
        parameters->start = i * 250;
        parameters->target_value = target_value;
        parameters->length = length;
        parameters->array = array;

        // Must maintain record of param structs for freeing later
        // params[i] = parameters;

        return_values[i] = (int) pthread_create( &thread_handle, NULL, linear_search_thread, (void *) parameters);
        threads[i] = thread_handle;

        // todo figure out if this is okay or if the parameters must remain persistent until thread is terminated
        free(parameters);
    }

    // Await threads to complete
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);

        // Free parameter structs
        // free(params[i]);

        if(!return_values[i]) {
            index = return_values[i];
        }
    }

    // Return index if target_value was found, otherwise -1

    return index;
}

void * linear_search_thread(void * parameters) {

    params_t * params = (params_t *) parameters;
    int start = params->start;

    // If this is the last interval, ensure that we don't check past the end of the array
    int end = start + 250 > params->length ? params->length : start + 250;

    int * array = params->array;

    for(int i = start; i < end; i++) {
        if(array[i] == params->target_value) {
            return (void *) i;
        }
    }
    return NULL;
}

char * get_mode() {
    return "mode: multi-thread";
}