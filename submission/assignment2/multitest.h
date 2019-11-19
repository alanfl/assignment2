//
// Created by alanfl and jmagnes362 on 11/12/19.
//

#ifndef MULTITEST_H
#define MULTITEST_H

// Usage: this function serves as the primary signature for the linear search implementation
int search(int * array, int length, int target_value);

// Usage: this function returns the mode that the current search implementation is in
char * get_mode();

// Usage: this function sets the interval size that the proc/thread runs in
void set_interval(int interval);

#endif //MULTITEST_H
