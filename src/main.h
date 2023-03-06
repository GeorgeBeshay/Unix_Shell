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
#include "strings_utilities.h"

// Global Definitions
#define BUFFER_SIZE 200
#define COMMAND_SIZE 30
#define MAX_PARAMETERS_NUMBER 10

// Functions Prototype
int main();

// Global Variables
extern char buffer[BUFFER_SIZE];
extern char command[COMMAND_SIZE];
extern char args[MAX_PARAMETERS_NUMBER][50];

#endif //LAB__01_MAIN_H