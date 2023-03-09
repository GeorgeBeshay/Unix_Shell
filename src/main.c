/*
 * Computer and Systems Engineering Department - Faculty Of Engineering - Alexandria University
 * CSE x61: Operating Systems - Lab #01 Processes
 * Student Name: George Samy Wahba Beshay
 */

#include "main.h"

char buffer[BUFFER_SIZE];
char command[COMMAND_SIZE];
char args[MAX_PARAMETERS_NUMBER][MAX_PARAMETER_SIZE];
int backgroundFlag;
int errorWhileScanning;


// ------------------ Main ------------------
int main(){
    /*
     * 1- Register the child signal to the appropriate signal handler
     * 2- Setup the working environment by choosing the declared
     *    path of the working directory, and printing an initialization statement.
     * 3- Run the shell
     * 4- When shell terminates, print a termination statement.
     */
    signal(SIGCHLD, childSignalHandler);
    setupEnvironment();
    shell();
    printTerminationStatement();
    return 0;
}

void setupEnvironment(){
    chdir(WORKING_DIRECTORY);
    printInitializationStatement();
}

void childSignalHandler(int signalNumber) {
    /*
     * Signal Number 17 indicates the signal was sent from a child process.
     */
    pid_t pid = waitpid(-1, NULL, WNOHANG);

    /*
     * = 0 indicates that there is a child process that
     *   is still under execution
     *   and so BY DEFAULT the waitpid will keep waiting
     * > 0 indicates that the child process terminated, and this value is
     *      the terminated process ID.
     */
    if(pid == -1 || pid == 0)
        return;
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
        evaluate();
//        printf("BUFFER IS: %s\n", buffer);
        prepareParams();
        if(errorWhileScanning){
            showInvalidCommandError();
            continue;
        }
        if(checkForTermination())
            break;
        if(checkForShellBuiltInCommand())
            executeShellBuiltIn();
        else
            executeCommand();
    }
    logProcessTermination(getpid());
}

void executeShellBuiltIn(){
    switch (checkForShellBuiltInCommand()) {
        case CD_FLAG:{
            int operationStatus = (strcmp(args[1], "~") == 0 || strcmp(args[1], "") == 0) ? chdir(HOME_PATH) : chdir(args[1]);
            if(operationStatus)
                showInvalidDirectoryError();
            else
                printf("Working directory has been changed to:\n%s\n", getcwd(NULL, 0));
            break;
        }
        case ECHO_FLAG: {
//            printf("In Echo\n");
//            showArgs();
            echoStatement();
            break;
        }
        case EXPORT_FLAG: {
//            printf("In Export\n");
            char* variableName = NULL, * variableValue = NULL;
            char tempString[strlen(args[1])];
            strcpy(tempString, args[1]);
            char** returned = getExportingData(variableName, variableName, (int)strlen(args[1]), tempString);
            if(returned != NULL) {
                variableName = returned[0];
                variableValue = returned[1];
//            if(getExportingData(variableName, variableValue, (int)strlen(args[1]), tempString) == 0) {
//                printf("!!Name = %s\n", variableName);
//                printf("!!Value = %s\n", variableValue);
                setenv(variableName, variableValue, 1);
//                printf("%s", getenv(variableName));

//            }
            }
            break;
        }
        default: {
            break;
        }
    }
}

void executeCommand(){
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

void evaluateExpression(){

}


