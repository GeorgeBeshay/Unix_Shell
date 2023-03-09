//
// Created by george on 3/6/23.
//

#include "strings_utilities.h"

void clearGlobalVars(){
    backgroundFlag = 0;
    errorWhileScanning = 0;
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

int stringContainsChar(char* word, char c){
    int ans = 0;
    for(int i = 0 ; i < (int)strlen(word) ; i++){
        if(word[i] == c)
            ans++;
    }
    return ans;
}

void prepareParams(){
    char bufferCopy[BUFFER_SIZE];
    strcpy(bufferCopy, buffer);
//    printf("Buffer Copy: %s\n", bufferCopy);
    char* word;
    int quotesFlag = 0;
//    int soloQuote = 0;
    int equalFlag = 0;
    // ------------------ Separator ------------------
    word = strtok(bufferCopy, " ");
    int i = 0;
//    printf("%s\n", word);
    while(word != NULL){
        if(stringContainsChar(word, '=') == 1 || stringContainsChar(word, '"') >= 1){
            // assuming that an = will always be followed by "
            equalFlag++;
            if(!quotesFlag)
                strcpy(args[i], word);
            else {
                strcat(args[i], " ");
                strcat(args[i], word);
            }
            strcat(args[i], " ");
            if(stringContainsChar(word, '"') == 2 || stringContainsChar(word, '"') == 0)
                quotesFlag = 0;
            else if(stringContainsChar(word, '"') == 1 && ((word[strlen(word)-1] != '"') || !quotesFlag))
                quotesFlag = 1;
            word = strtok(NULL, " ");
        }
        else if(!quotesFlag) {
            if(stringContainsChar(word, '"')) {
                quotesFlag = 1;
            }
            strcpy(args[i], word);
            word = strtok(NULL, " ");
            if(!quotesFlag)
                i++;
        } else {
            if(word[strlen(word) - 1] == '"'){
                quotesFlag = 0;
            }
            strcat(args[i], " ");
            strcat(args[i], word);
            word = strtok(NULL, " ");
            if(!quotesFlag)
                i++;
        }
    }
    /*
     * export x=" $x "
     * export x="213423"
     * export asdsad=eerr
     * export erw32="s wer wer"
     */
//    if(quotesFlag)
    if(stringContainsChar(buffer, '"') % 2 == 1)
        errorWhileScanning = 1;
    strcpy(command, "");
    strcat(command, "/bin/");
    strcat(command, args[0]);
    // ------------------ Separator ------------------
//    showArgs();
}

int checkForTermination(){
    const char* exitStatement = "exit ";
    if(compareBufferTo(exitStatement))
        return EXIT_FLAG;
    return 0;
}

void evaluate(){
    int varFlag = (stringContainsChar(buffer, '$') == 1) ? 1 : 0;
    if(varFlag){
        char bufferCopy[strlen(buffer)];
        char* varName;
        char* varValue;
        strcpy(bufferCopy, buffer);
        int found = -1;
        int i = 0;
        for( ; i < strlen(bufferCopy) ; i++){
            if(found != -1){
                varName = &(bufferCopy[i]);
                int len = 0;
                while(bufferCopy[i] != ' ' && bufferCopy[i] != '"' && i < strlen(bufferCopy)) {
                    i++;
                    len++;
                }
                bufferCopy[i] = '\0';
                varValue = getenv(varName);
                printf("Var Value = %s\nVar Name = %s\n", varValue, varName);
                i++;
                break;
            }
            if(bufferCopy[i] == '$')
                found = i;
            if(i >= strlen(bufferCopy))
                break;
        }
        if(found != -1){
//            printf("HEREEE %d\n", i);
            int j = 0; // varValue index
            for( ; j < strlen(varValue) ; j++){
                buffer[found] = varValue[j];
                found++;
            }
            for(; i < strlen(buffer) ; i++){
                buffer[found] = bufferCopy[i];
                found++;
            }
        }
    }
}

void echoStatement(){
    if(stringContainsChar(args[1], '"') == 2) {
        char tempS[strlen(args[1])-2];
        for (int i = 1; i < strlen(args[1])-1; i++) {
                tempS[i] = args[1][i];
        }
        printf("%s\n", args[1]);
    } else
        printf("%s\n", args[1]);
//    char s[500];
//    char varName[500];
//    int j = 0, i = 0, k = 0;
//    strcpy(s, args[1]);
//    while(i < strlen(args[1])){
//        if(args[1][i] == '"') {
//            i++;
//            continue;
//        }
//        if(args[1][i] == '$'){
//            i++;
//            while(args[1][i] != '\0' && args[1][i] != ' ' && i < strlen(args[1])){
//                varName[k++] = args[1][i++];
//            }
//            char varName2[k];
//            for(int o = 0 ; o < k ; o++){
//                varName2[o] = varName[o];
//            }
//            char* tempS = getenv(varName2);
//            printf("%s\n", tempS);
//            while(*tempS != '\0' && tempS != NULL){
//                s[j++] = *tempS;
//                tempS++;
//            }
//            printf("Here %s\n", tempS);
//        } else {
//            s[j++] = args[1][i++];
//        }
//    }
//    printf("%s\n%s", s, varName);
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

char** getExportingData(char* variable, char* value, int x, char tempString[x]){
    int i = 0;
    variable = &tempString[0];
    while(tempString[i] != '=' && tempString[i] != '\0'){
        i++;
    }
    tempString[i++] = '\0';
    if(tempString[i] == '"')
        i++;
    value = &(tempString[i]);
    while(tempString[i] != '"' && tempString[i] != '\0'){
        i++;
    }
    if(tempString[i] == '"')
        tempString[i] = '\0';
    printf("Name = %s\n", variable);
    printf("Value = %s\n", value);
    char* temp[2] = {variable, value};
    char** returnThis = temp;
    return returnThis;
//    return 0;
}