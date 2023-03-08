//
// Created by george on 3/7/23.
//

#ifndef SRC_ASSISTANT_H
#define SRC_ASSISTANT_H

#include "main.h"

// Functions Prototype
void printInitializationStatement();
void printSeparator();
void showInvalidCommandError();
void showProcessNegIDError();
void printTerminationStatement();
void logProcessTermination(int ProcessID);
void clearTheNewLine(char* s);
void showInvalidDirectoryError();

#endif //SRC_ASSISTANT_H
