//
// Created by george on 3/5/23.
//

#include "main.h"

char buffer[BUFFER_SIZE];
char command[COMMAND_SIZE];
char args[MAX_PARAMETERS_NUMBER][50];

// ------------------ Main ------------------
int main(){
    // Generating Shell
    system("clear");
    printf("%s\t\t\tOperating Systems Course - Unix Shell Lab\n\t\t\tShell Is Operating\n", KCYN);
    printf("----------------------------------------------------------------------------\n");
    while(1){
        printf("\nEnter Command To Execute:\n");
        // Clear Global variables to assure that no commands overlap
        clearGlobalVars();
        scanInput();            // Scan the user command
        prepareParams();        // divide the entered command to a command and args
//        showArgs();
        if(checkForTermination())   // if command was "exit", shell will terminate
            break;
        // fork() is the essential method to create a new process
        pid_t processID = fork();
        if(processID > 0) {         // parent process
            wait(NULL);     // wait for child process
            printf("-----------------------------\n");
        } else if(processID == 0) { // child process
            execvp(command, prepareArgsPointer());      // execute command
            // in case of wrong command the following lien will be reached
            printf("%sINVALID COMMAND%s\n", KRED, KCYN);
            return 0;
        } else {
            printf("%sAn Error Had Occurred, Negative Process ID was found.%s", KRED, KCYN);
            return 1;
        }
    }
    printf("Finished\n");
    system("clear");
    return 0;
}
