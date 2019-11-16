//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#include <unistd.h>
#include <stdlib.h>

int search(int * array, int length, int target_value);

int linear_search_process(int * array, int length, int start, int target_value);

char * get_mode();



char * get_mode() {
    return "mode: multi-process";
}