//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>

void fill_array(int * array, int length);
void scramble_array(const int * array, int length);

int main(int argc, char** argv) {

    int * array = malloc(10000 * sizeof(int));

    fill_array(array, 10000);

    int index = search(array, 10000, 9999);


    printf("Currently in %s\n", get_mode());
    printf("Target value '9999' was found at index: %d\n", index);

    return 0;
}

void fill_array(int * array, int length) {
    for(int i = 0; i < length; i++) {
        array[i] = i;
    }
}

void scramble_array(const int * array, int length) {

    for(int i = 0; i < (2*length)/3; i++) {

    }

}