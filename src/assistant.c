//
// Created by george on 3/7/23.
//

#include "assistant.h"


/*
 * Functions Prints initialization statements as a feed back for the user on
 * running the shell.
 */
void printInitializationStatement(){
    system("clear");
    printf("%s\t\t\tOperating Systems Course - Unix Shell Lab\n\t\t\tShell Is Operating\n", KCYN);
    printf("----------------------------------------------------------------------------\n");
}

void printSeparator(){
    printf("---------------------- Separator ----------------------");
}

/*
 * In case of inserting an invalid command, an error msg should be displayed.
 */
void showInvalidCommandError(){
    printf("%sINVALID COMMAND%s\n", KRED, KCYN);
}

/*
 * in case the machine can't spawn any more processes, an error should be displayed.
 */
void showProcessNegIDError(){
    printf("%sAn Error Had Occurred, Negative Process ID was found.%s", KRED, KCYN);
}

void printTerminationStatement(){
    printf("Finished\n");
    system("clear");
}

/*
 * The following function accepts the terminated process id, then log it in
 * the logging file.
 */
void logProcessTermination(int processID){
    time_t rawTime;
    time(&rawTime);
    char* logStatement = asctime(localtime(&rawTime));      // will insert a \n at the end
    clearTheNewLine(logStatement);
    FILE* loggingFile = fopen("../ProcessesTerminationLogFile.txt", "a");
    fputs("@ - ", loggingFile);
    fputs(logStatement, loggingFile);
    fprintf(loggingFile, "\b - Process [%d] Terminated.\n", processID);
    fclose(loggingFile);
}

/*
 * supporting method, used to remove the \n at the end of a string.
 */
void clearTheNewLine(char* s){
    char* copy = s;
    while(* copy != '\n')
        copy++;
    *copy = '\0';
}
