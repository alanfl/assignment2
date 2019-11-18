//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> //gcc -lm
#include <sys/time.h>

void fill_array(int * array, int length);
void scramble_array(int * array, int length);
void swap(int * array, int index, int length);
int test_search(int * array, int target, int length); //temp
long minimum(long * array`, int length);
long maximum(long * array, int length);
double array_mean(long * array, int length);
double array_stdDeviation(long * array, double mean, int length);
void evaluate_results(long * array, int length);
void search_A(int * array, int length);
void search_B(int * array, int length);
void search_C(int * array, int length);
void search_D(int * array, int length);

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
	
	//sets length of array to be used for searching
	int length = 100, i;
	int * array = malloc(sizeof(int) * length);
	fill_array(array, length);
	scramble_array(array, length);

	//testing
	/*
	for(i = 0; i < length; i++){
		printf("%d\n", array[i]);
	}
	*/

	//call workloads that will test and print all relevant data
	search_A(array, length);
	search_B(array, length);
	search_C(array, length);
	search_D(array, length);

	//free array
	free(array);

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
	array[index] = temp;
	next = rand() % length;
	array[index] = array[next];
	array[next] = temp;
}

//unknown purpose yet
void search_A(int * array, int length){
	//print about this test

	int size = 100;//how many times this will run
	long * results = malloc(sizeof(long) * size);
	int i, index = -1, target, next;
	for(i = 0; i < size; i++){
		results[i] = 0;
	}

	target = rand() % 100; //target will not change, but will be moved
		
	for(i = 0; i < size; i++){
		if(index != -1){
			swap(array, index, length);
		}
		
		//measure length of the search
		//start time
		struct timeval start, end;
		gettimeofday(&start, NULL);	
	
		index = test_search(array, length, target);
		
		//end time
		gettimeofday(&end, NULL);
		long seconds = end.tv_sec - start.tv_sec;
		long microseconds = end.tv_usec - start.tv_usec;
		long timeElapsed = ((seconds * 1000000) + microseconds);
		results[i] = timeElapsed;
		//printf("%ld\n", timeElapsed);

	}
	
	evaluate_results(results, size);
	free(results);
}



void search_B(int * array, int length){

}

void search_C(int * array, int length){

}

void search_D(int * array, int length){

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
	
	//printf("Sum = %f\n", sum);
	stdDev = sqrt(sum / (double)length);
	return stdDev;
}

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

//test search while libraries are incomplete
int test_search(int * array, int target, int length){
	int x, i;
	
	//runtimes were between 0 and 1 microseconds with this search	
	for(i = 0; i < 10000; i++){

	}

	for(i = 0; i < length; i++){
		x = array[i];
		if(x == target){
			return i;
		}
	}

	return -1;
}
