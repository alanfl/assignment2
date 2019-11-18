//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

const int PROCESS_INTERVAL = 250;

int search(int * array, int length, int target_value);

void linear_search_process(int * array, int length, int start, int target_value);

char * get_mode();

int search(int * array, int length, int target_value) {

    int index = -1;

    int num_processes = length / PROCESS_INTERVAL + 1;

    // Process array to store process ids
    pid_t processes[num_processes];

    for(int i = 0; i < num_processes;i ++) {

        // Store record of all processes in array
        // Child process
        if((processes[i] = fork()) == 0) {
            // Begin search within interval
            linear_search_process(array, length, i * PROCESS_INTERVAL, target_value);
        }
        // Error, report failure
        else if(processes[i] < 0) {
            exit(-1);
        }
        // Parent, do nothing and loopback
        else {

        }
    }

    // Now begin waiting for processes
    for(int i = 0; i < num_processes; i++) {
        int status;
        waitpid(processes[i], &status, 0);

        int interval_index = WEXITSTATUS(status);

        // Since status can only hold up to 8 bits, we must
        // compute the overall location by using interval sizes
        if(interval_index != 255) {
            index = i * PROCESS_INTERVAL + interval_index;
        }
    }

    return index;
}

void linear_search_process(int * array, int length, int start, int target_value) {

    // If this is the last interval, ensure that we don't check past the end of the array
    int end = start + PROCESS_INTERVAL > length ? length : start + PROCESS_INTERVAL;

    // Iterate within its interval
    for(int i = start; i < end; i++) {
        if(array[i] == target_value) {

            // Must compute the index within the interval because if the array is sufficiently large enough,
            // we will not be able to pass it out to the parent
            int interval_index = i % PROCESS_INTERVAL;
            exit(interval_index);
        }
    }

    exit(-1);
}

char * get_mode() {
    return "mode: multi-process";
}