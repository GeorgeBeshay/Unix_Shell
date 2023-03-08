//
// Created by george on 3/6/23.
//

#include "strings_utilities.h"

void clearGlobalVars(){
    backgroundFlag = 0;
    strcpy(buffer, "");
    strcpy(command, "");
    for(int i = 0 ; i < MAX_PARAMETERS_NUMBER ; i++)
        strcpy(args[i], "");
}

void filterBuffer(){
    int whiteSpacesCount = 0;
    if(strlen(buffer) > 0){
        while(whiteSpacesCount < strlen(buffer) && buffer[whiteSpacesCount] == ' ')
            whiteSpacesCount++;
    }
    if(whiteSpacesCount > 0) {
        char tempBufferCopy[BUFFER_SIZE];
        strcpy(tempBufferCopy, buffer);
        for (int i = whiteSpacesCount ; i < BUFFER_SIZE + whiteSpacesCount ; i++){
            buffer[i - whiteSpacesCount] = tempBufferCopy[i];
        }
    }
}

void scanInput(){
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strlen(buffer)-1] = '\0';
    if(buffer[strlen(buffer)-1] == '&') {
        backgroundFlag = 1;
        buffer[strlen(buffer)-1] = '\0';
    }
    filterBuffer();
}

char** prepareArgsPointer(){
    int c = 0;
    for(int i = 0 ; i < MAX_PARAMETERS_NUMBER ; i++){
        if(strcmp(args[i], "") == 0){
            break;
        } else
            c++;
    }
    char** pt = malloc((c+1) * sizeof(char*));
    for(int i = 0 ; i < c ; i++)
        pt[i] = args[i];
    pt[c] = NULL;
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
    const char* exitStatement = "exit ";
    if(compareBufferTo(exitStatement))
        return EXIT_FLAG;
    return 0;
}

int compareBufferTo(const char* commandToCompareWith){
    int commandLength = strlen(commandToCompareWith);
    if(strlen(buffer) >= commandLength - 1){
        int i = 0;
        int maxLen = (strlen(buffer) == commandLength - 1) ? commandLength - 1 : commandLength;
        for( ; i < maxLen ; i++){
            if(buffer[i] != commandToCompareWith[i])
                break;
        }
        if(i == maxLen)
            return 1;
    }
    return 0;
}

int checkForShellBuiltInCommand(){
    const char* cdCommand = "cd ";
    if(compareBufferTo(cdCommand))
        return CD_FLAG;
    const char* echoCommand = "echo ";
    if(compareBufferTo(echoCommand))
        return ECHO_FLAG;
    const char* exportCommand = "export ";
    if(compareBufferTo(exportCommand))
        return EXPORT_FLAG;
    return 0;
}