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
#include <signal.h>
#include <sys/resource.h>
#include <time.h>

#include "strings_utilities.h"
#include "colors.h"
#include "assistant.h"

// Global Definitions
#define BUFFER_SIZE 1000
#define COMMAND_SIZE 100
#define MAX_PARAMETERS_NUMBER 10
#define MAX_PARAMETER_SIZE 100
#define WORKING_DIRECTORY "../Working_Directory"
#define CD_FLAG 7
#define ECHO_FLAG 8
#define EXPORT_FLAG 9
#define EXIT_FLAG 10
#define HOME_PATH getenv("HOME")

// Functions Prototype
int main();
void shell();
void childSignalHandler(int signalNumber);
void setupEnvironment();
void evaluate_expression();
void executeCommand();
void executeShellBuiltIn();
void evaluateExpression();

// Global Variables
extern char buffer[BUFFER_SIZE];
extern char command[COMMAND_SIZE];
extern char args[MAX_PARAMETERS_NUMBER][MAX_PARAMETER_SIZE];
extern int backgroundFlag;
extern int errorWhileScanning;

#endif //SRC_MAIN_H