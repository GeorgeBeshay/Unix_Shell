//
// Created by george on 3/5/23.
//

#include "main.h"

// ------------------ Main ------------------
int main(){
    for(int i = 0 ; i < 3 ; i++){
        scanInput();
        printf("%s\n", buffer);
        printf("%lu\n", strlen(buffer));
        if(checkForTermination())
            break;
    }
    printf("Finished\n");
    return 0;
}

void scanInput(){
    fgets(buffer, 200, stdin);
    buffer[strlen(buffer)-1] = '\0';
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