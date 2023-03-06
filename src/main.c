//
// Created by george on 3/5/23.
//

#include "main.h"

char buffer[BUFFER_SIZE];
char command[COMMAND_SIZE];
char args[MAX_PARAMETERS_NUMBER][50];

// ------------------ Main ------------------
int main(){
    system("clear");
    printf("\t\t\tOperating Systems Course - Unix Shell Lab\n\t\t\tShell Is Operating\n");
    printf("----------------------------------------------------------------------------\n\n");
    while(1){
        printf("\nEnter Command To Execute:\n");
        clearGlobalVars();
        scanInput();
        prepareParams();
//        showArgs();
        if(checkForTermination())
            break;
        if(fork() != 0)
            wait(NULL);
        else {
            execvp(command, prepareArgsPointer());
            return 0;
        }
    }
    printf("Finished\n");
    return 0;
}
