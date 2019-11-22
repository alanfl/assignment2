//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

void fill_array(int * array, int length);
void scramble_array(int * array, int length);
void swap(int * array, int index, int length);
long minimum(long * array, int length);
long maximum(long * array, int length);
double array_mean(long * array, int length);
double array_stdDeviation(long * array, double mean, int length);
void evaluate_results(long * array, int length);
void run_search(int * array, int length, int interval, int testPlan);

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
	//check for arguments
	if(argc > 3){
		printf("Error: Too many arguments\n");
		return 0;
	}else if(argc < 3){
		printf("Error: Not enough arguments\n");
		return 0;
	}	
	
	//make sure interval isnt too large, no negative inputs
	int testPlan, i;
	int length = atoi(argv[1]), interval = atoi(argv[2]);	
	if(length < 0 || interval < -1){
		printf("Error: Invalid input\n");
		return 0;
	}else if(interval > 250){
		printf("Error: Interval too large\n");
		return 0;
	}else if(interval == -1){
		testPlan = 2;
	}else if(length < 10000){ //all of test plan 1 is less than 10k
		testPlan = 1;
	}else{
		testPlan = 3; //extremes test
	}
	
	//sets length of array to be used for searching
	int * array = malloc(sizeof(int) * length);
	fill_array(array, length);
	scramble_array(array, length);

	if(testPlan == 2){
		for(i = 1; i <= 50; i++){
			//check if length is divisible by this number of 
			//procs/threads and calculate interval
			if((length % i) == 0){
				int newInterval = length / i;
				if(newInterval > 250){
					continue;
				}
				set_interval(newInterval); 
				run_search(array, length, newInterval, testPlan);
				//make output neater
				if(i != 50){
					printf("\n");
				}
			}
		}
	}else{
		set_interval(interval);
		run_search(array, length, interval, testPlan);
	}

	//free arrays
	free(array);

	return 0;
}

void run_search(int * array, int length, int interval, int testPlan){
	//get mode and print
	char* mode = get_mode();
	printf("%s\n", mode);		
	int i, size = 100; //how many times this will run
	long * results = malloc(sizeof(long) * size);
	int index = -1, target;
	for(i = 0; i < size; i++){
		results[i] = 0;
	}

	printf("Running Test %d: Length = %d, Interval = %d\n", testPlan, length, interval);

	target = rand() % length; //target will not change, but will be moved
	for(i = 0; i < size; i++){
		if(index != -1){//after the first run, target will be moved
			swap(array, index, length);
		}
		
		printf("Iteration %d\n", i);

		//measure length of the search
		//start time
		struct timeval start, end;
		gettimeofday(&start, NULL);	
	
		index = search(array, length, target);

		//end time
		gettimeofday(&end, NULL);
		long seconds = end.tv_sec - start.tv_sec;
		long microseconds = end.tv_usec - start.tv_usec;
		long timeElapsed = ((seconds * 1000000) + microseconds);
		results[i] = timeElapsed;
	}

	evaluate_results(results, size);
	free(results);


}

void fill_array(int * array, int length) {
	int i;
	for(i = 0; i < length; i++){
		array[i] = i;
	}
}

void scramble_array(int * array, int length) {
	int i, first, second, temp;
    	for(i = 0; i < (3*length)/4; i++) {
		first = rand() % length;
		second = rand() % length;
		temp = array[second];
		array[second] = array[first];
		array[first] = temp;
   	}
}

//swaps location of target randomly
void swap(int * array, int index, int length){
	int temp, next;
	temp = array[index];
	next = rand() % length;
	array[index] = array[next];
	array[next] = temp;
}

//helper functions to determine min, max, mean, and standard deviation
long minimum(long * array, int length){
	long min = array[0], i, x;
	for(i = 1; i < length; i++){
		x = array[i];
		if(x < min){
			min = x;
		}
	}
	
	return min;
}

long maximum(long * array, int length){
	long max = array[0], i, x;
	for(i = 1; i < length; i++){
		x = array[i];
		if(x > max){
			max = x;
		}
	}

	return max;
}

double array_mean(long * array, int length){
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
double array_stdDeviation(long * array, double mean, int length){
	int i;
	double sum = 0.0, stdDev = 0.0;	
	for(i = 0; i < length; i++){
		sum += pow((double)array[i] - mean, 2);
	}
	
	stdDev = sqrt(sum / (double)length);
	return stdDev;
}

//calculates and prints all of the results
void evaluate_results(long * array, int length){
	long min, max;
	double mean, stdDev;
	min = minimum(array, length);
	max = maximum(array, length);
	mean = array_mean(array, length);
	stdDev = array_stdDeviation(array, mean, length);
	printf("Min = %ld microseconds\n", min);
	printf("Max = %ld microseconds\n", max);
	printf("Mean = %f microseconds\n", mean);
	printf("Standard Deviation = %f microseconds\n", stdDev);
}
