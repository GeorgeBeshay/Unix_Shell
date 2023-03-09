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
    int width = 70;
    char text1[] = "Computer and Systems Engineering Department ";
    char text2[] = "Faculty of Engineering - Alexandria University";
    char text3[] = "Spring 2023 - CSE x61: Operating Systems";
    char text4[] = "Unix Shell Program";
    int padding1 = (width - (int)strlen(text1)) / 2;
    int padding2 = (width - (int)strlen(text2)) / 2;
    int padding3 = (width - (int)strlen(text3)) / 2;
    int padding4 = (width - (int)strlen(text4)) / 2;
    printf("\033[1;33m"); // set text color to yellow
    printf("************************************************************************\n");
    printf("*%*s%*s*\n", padding1 + (int)strlen(text1), text1, padding1, "");
    printf("*%*s%*s*\n", padding2 + (int)strlen(text2), text2, padding2, "");
    printf("*%*s%*s*\n", padding3 + (int)strlen(text3), text3, padding3, "");
    printf("*%*s%*s*\n", padding4 + (int)strlen(text4), text4, padding4, "");
    printf("************************************************************************\n");
    printf("\033[0m"); // reset text color to default
//    printf("%s\t\t\tOperating Systems Course - Unix Shell Lab\n\t\t\tShell Is Operating\n", KCYN);
//    printf("----------------------------------------------------------------------------\n");
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

void showInvalidExportError(){
    printf("%sINVALID EXPORT STATEMENT%s\n", KRED, KCYN);
}

void showInvalidDirectoryError(){
    printf("%sINVALID DIRECTORY%s\n", KRED, KCYN);
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
    FILE* loggingFile = fopen("ProcessesTerminationLogFile.txt", "a");
    fputs("@ - ", loggingFile);
    fputs(logStatement, loggingFile);
    fprintf(loggingFile, "\b - Process [%d] Terminated.\n", processID);
    fclose(loggingFile);
    printf("%s%d Logged & Terminated\n%s", KGRN, processID, KCYN);
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
