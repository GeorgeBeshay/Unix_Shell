//
// Created by george on 3/6/23.
//

#include "strings_utilities.h"

void clearGlobalVars(){
    strcpy(buffer, "");
    strcpy(command, "");
    for(int i = 0 ; i < MAX_PARAMETERS_NUMBER ; i++)
        strcpy(args[i], "");
}

void scanInput(){
    fgets(buffer, 200, stdin);
    buffer[strlen(buffer)-1] = '\0';
}

char** prepareArgsPointer(){
    int c = 0;
    for(int i = 0 ; i < MAX_PARAMETERS_NUMBER ; i++){
        if(strcmp(args[i], "") == 0){
            break;
        } else
            c++;
    }
    char** pt = malloc(c * sizeof(char*));
    for(int i = 0 ; i < c ; i++)
        pt[i] = args[i];
    return pt;
}

void showArgs(){
    for(int i = 0 ; i < MAX_PARAMETERS_NUMBER ; i++){
        if(strcmp(args[i], "") == 0)
            break;
        printf("%s, ", args[i]);
    }
    printf("\n");
}

void prepareParams(){
    char bufferCopy[BUFFER_SIZE];
    strcpy(bufferCopy, buffer);
//    printf("%s\n", bufferCopy);
    char* word;
    // ------------------ Separator ------------------
    word = strtok(bufferCopy, " ");
    int i = 0;
    while(word != NULL){
        strcpy(args[i], word);
        i++;
        word = strtok(NULL, " ");
    }
    strcpy(command, "");
    strcat(command, "/bin/");
    strcat(command, args[0]);
    // ------------------ Separator ------------------
}

int checkForTermination(){
    const char* exitStatement = "exit";
    if(strlen(buffer) == 4){
        int i = 0;
        for( ; i < 4 ; i++){
            if(buffer[i] != exitStatement[i])
                break;
        }
        if(i == 4)
            return 1;
    }
    return 0;
}