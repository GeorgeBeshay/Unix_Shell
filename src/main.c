//
// Created by george on 3/5/23.
//

#include "main.h"

char buffer[BUFFER_SIZE];
char command[COMMAND_SIZE];
char args[MAX_PARAMETERS_NUMBER][50];
int backgroundFlag;


// ------------------ Main ------------------
int main(){
    printInitializationStatement();
    signal(SIGCHLD, childSignalHandler);
    shell();
    printTerminationStatement();
    return 0;
}

void childSignalHandler(int signalNumber) {
    /*
     * Signal Number 17 indicates the signal was sent from a child process.
     */
    pid_t pid = waitpid(-1, NULL, WNOHANG);

    /*
     * = 0 indicates that the child process is still under execution
     *   and so BY DEFAULT the waitpid will keep waiting
     * > 0 indicates that the child process terminated, and this value is
     *      the terminated process ID.
     */
    if(pid == -1)
        return;
    printf("%d Terminated\n", pid);
    /*
     * Code to log terminated process ID in the logging file.
     */
    logProcessTermination(pid);
}

void shell(){
    while(1){
        printf("\nEnter A Command To Execute:\n");
        clearGlobalVars();
        scanInput();
        prepareParams();
        if(checkForTermination())
            return;
        pid_t processID = fork();
        if(processID > 0) {
            printf("Parent Process ID: %d \n", getpid());
            if(!backgroundFlag) {
                wait(NULL);
                logProcessTermination(processID);
            }
            printSeparator();
        } else if(processID == 0) {
            printf("Child Process ID: %d\n", getpid());
            execvp(command, prepareArgsPointer());
            showInvalidCommandError();
            exit(0);
        } else {
            showProcessNegIDError();
            perror("Fork Error");
            exit(EXIT_FAILURE);
        }
    }
}


