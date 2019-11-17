//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> //gcc -lm
#include <sys/time.h>

void fill_array(int * array, int length);
void scramble_array(const int * array, int length);
int test_search(int * array, int target, int length); //temp
char * get_mode(); //temp
long minimum(int * array, int length);
long maximum(int * array, int length);
double array_mean(int * array, int length);
double array_stdDeviation(int * array, double mean, int length);

/*
When run, your code should print out:
	- which multi-mode it is in (-process or -thread)
	- which test from your testplan document is being run
		- the parameters of the test
		- which iteration is being run
	- the results (time) of each test
		- the aggregate results of a test batch once completed (min, max, average, standard deviation)
*/

int main(int argc, char** argv) {
	//get mode and print
	char* mode = get_mode();
	printf("%s\n", mode);
	
	int length = 10, i;
	int * array = malloc(sizeof(int) * length);
	for(i = 0; i < length; i++){
		array[i] = i;
	}


	//testing functions for results, can be made a function later
	long min, max;
	double mean, stdDev;
	min = minimum(array, length);
	max = maximum(array, length);
	mean = array_mean(array, length);
	stdDev = array_stdDeviation(array, mean, length);
	printf("Min = %ld\n", min);
	printf("Max = %ld\n", max);
	printf("Mean = %f\n", mean);
	printf("Standard Deviation = %f\n", stdDev);

	return 0;
}

void fill_array(int * array, int length) {

    int * temp = malloc(sizeof(int) * length);

    if(temp == NULL) {
        exit(1); // Temporary exit
    }

    array = temp;
	int i = 0;
    for(i = 0; i < length; i++) {
        array[i] = i;
        i++;
    }
}

void scramble_array(const int * array, int length) {
	int i = 0;
    for(i = 0; i < (2*length)/3; i++) {



    }

}


//testing function while libraries are incomplete
//change to return how long it took to find target
int test_search(int * array, int target, int length){
		
	int x, i;
	for(i = 0; i < length; i++){
		x = array[i];
		if(x == target){
			return i;
		}
	}

	return -1;
}


//testing function while libraries are incomplete
char * get_mode() {
    return "mode: test";
}

//helper functions to determine min, max, mean, and standard deviation
long minimum(int * array, int length){
	int min = array[0], i, x;
	for(i = 1; i < length; i++){
		x = array[i];
		if(x < min){
			min = x;
		}
	}
	
	return min;
}

long maximum(int * array, int length){
	int max = array[0], i, x;
	for(i = 1; i < length; i++){
		x = array[i];
		if(x > max){
			max = x;
		}
	}

	return max;
}

double array_mean(int * array, int length){
	long sum = 0;
	double mean = 0.0;
	int i = 0;
	for(i = 0; i < length; i++){
		sum += array[i];
	}

	mean = (double)sum / (double)length; 
	return mean;
}

//sd = sqrt((value-mean)^2 / length)
//must compile with -lm to link math.h
double array_stdDeviation(int * array, double mean, int length){
	int i;
	double sum = 0.0, stdDev = 0.0;	
	for(i = 0; i < length; i++){
		sum += pow((double)array[i] - mean, 2);
	}
	
	//printf("Sum = %f\n", sum);
	stdDev = sqrt(sum / (double)length);
	return stdDev;
}


