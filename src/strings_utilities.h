//
// Created by george on 3/6/23.
//

#ifndef SRC_STRINGS_UTILITIES_H
#define SRC_STRINGS_UTILITIES_H

#include "main.h"

// Functions Prototype
void scanInput();
char** prepareArgsPointer();
void prepareParams();
void showArgs();
int checkForTermination();
void clearGlobalVars();
void filterBuffer();
int compareBufferTo(const char* commandToCompareWith);
int checkForShellBuiltInCommand();

#endif //SRC_STRINGS_UTILITIES_H
