//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>

void fill_array(int * array, int length);
void scramble_array(const int * array, int length);

int main(int argc, char** argv) {

    return 0;
}

void fill_array(int * array, int length) {

    int * temp = malloc(sizeof(int) * length);

    if(temp == NULL) {
        exit(1); // Temporary exit
    }

    array = temp;

    for(int i = 0; i < length; i++) {
        array[i] = i;
        i++;
    }
}

void scramble_array(const int * array, int length) {

    for(int i = 0; i < (2*length)/3; i++) {



    }

}