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

/*
When run, your code should print out:
	- which multi-mode it is in (-process or -thread)
	- which test from your testplan document is being run
		- the parameters of the test
		- which iteration is being run
	- the results (time) of each test
		- the aggregate results of a test batch once completed (min, max, average, standard deviation)
*/

/*
You should compare Process and thread runtimes on different amounts of data. Make sure your steps in data size are significant based on what you want to test. You should determine:
			- a general trend of: time vs. size of list to search for Processes as well as time vs. size of list to search for threads
			- a tradeoff point for Processes vs threads
				i.e. how long a list would cause threads to perform at the same rate as a Process
					e.g. perhaps, if you create a new thread/Proc for every 250 integers, then searching a list of 5000 integers using threads (requiring 20 threads) is as fast as searching a list of 250 integers using a single Process
			- a tradeoff point for parallelism for Processes and threads
				i.e. at what point does splitting the work over more Processes/threads make the task take longer than not doing so?
					e.g. perhaps sorting a list of 250 elements, but splitting it up in to lists of size 10 (requiring 25 threads) is slower than splitting it up in to lists of size 11 (requiring 22 threads)
*/

//Your code should split the list of numbers given in to groups of no more than 
//250 values and create another Process or thread to search each.


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
	int length = atoi(argv[1]), interval = atoi(argv[2]);	
	if(length < 0 || interval < 0){
		printf("Error: Invalid input\n");
		return 0;
	}else if(interval > 250){
		printf("Error: Interval too large\n");
		return 0;
	}

	set_interval(interval);

	//get mode and print
	char* mode = get_mode();
	printf("%s\n", mode);
	
	//sets length of array to be used for searching
	int * array = malloc(sizeof(int) * length);
	fill_array(array, length);
	scramble_array(array, length);

	//implement test here
	int i, size = 100; //how many times this will run
	long * results = malloc(sizeof(long) * size);
	int index = -1, target;
	for(i = 0; i < size; i++){
		results[i] = 0;
	}

	target = rand() % length; //target will not change, but will be moved
	for(i = 0; i < size; i++){
		if(index != -1){//after the first run, target will be moved
			swap(array, index, length);
		}
		
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
	
	//free arrays
	free(array);
	free(results);

	return 0;
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
