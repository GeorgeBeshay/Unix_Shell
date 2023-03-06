//
// Created by george on 3/5/23.
//

#ifndef SRC_MAIN_H
#define SRC_MAIN_H

// Including Required Modules
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Functions Prototype
int main();
void scanInput();
int checkForTermination();

// Global Variables
char buffer[200];

#endif //LAB__01_MAIN_H