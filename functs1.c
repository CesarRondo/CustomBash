/*
By:
Cesar Rondo Rodriguez
email: c.rondoro12@gmail.com
*/


#include "headers.h"
//#include <config.h>//for automake

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> //POSIX only
#include <errno.h>
#include <fcntl.h> //dup2 constants





///* Signal handler for Ctrl+C
void signalHandler(int sigCode){
    printf("\n");
    printTime();
    printf("# ^C\n");
    printTime();
    printf("# ");
    fflush(stdout);
    //printf("\n#Crtl+C pressed\n");
    //printf("# ");
}


void handleCD(char **argArr){

    int resultCode;
    if(argArr[1]== NULL || argArr[1]=="~"){
        //no arguments so we change to the HOME directory
        resultCode=chdir(getenv("HOME"));
        //printf("result code:%d\n", resultCode);
    }
    else{
        //just read 1st argument and ignore the rest
        resultCode=chdir(argArr[1]);
        //printf("result code:%d\n", resultCode);
    }
    if(resultCode!=-1){
        printf("cd: ");
        fflush(stdout);
        char *tempArr[]={"pwd",NULL};
        runCommand("pwd",tempArr);
    }
    else{
        printf("cd: ");
        fflush(stdout);
        perror(argArr[1]);
    }

}

int runCommand(char *command,char ** argArr){
    int execSuccess;
    pid_t childID = fork();
    if(childID==-1){
        printf("fork failed: \nthere was an error and the command could not be ran, please try again\n");
       exit(-1);
    }
    else if(childID==0){
        execSuccess=execvp(command,argArr); //when child node finishes the task or command it exits by itself
        if(execSuccess==-1){
            if(strcmp(command,argArr[0])==0){
                printf("command %s is not recognised\n", command);
            }
            else{
                printf("command %s is not recognised\n", command);
            }
        }
        exit(0);
    }
    wait(NULL);

    return execSuccess;
}

int findRedirect(char *buffer, int buffLen){ // find the index of > to know if we need to redirect the output to a file
    char c=buffer[0];
    



    int i=1;
    int foundRedirect=0;
    while(c!='\0' && buffer!=NULL){
        c=buffer[i];
        if(c=='>'){
            foundRedirect=1;
            break;
        }
        i++;
    }
    if(i==buffLen+1){//if end of buffer reached no > found (we add one because i reached \o and buffLen doesnt count it)
        return -1;
    }
    else{
        //> found, but we must check that there is a command behind ">"
        for(int j=0;j<i;j++){
            if(buffer[j]!=' ' && buffer[j]!='>'){
                return i;//we return the index of > if there is a command
            }
        }

        return -1;
    }

    
}

void redirect(char *buffer){//this function runs and redirects a command to the requested file
        
        char* token = strtok(buffer,">");
        char* command = token;  //get the command : everything before >
        buffer=token;
        token =strtok(NULL," "); //read next word after > and ignore the rest

        //printf("%s\n", command);
        printf("opening and editing file: <%s>\n",token);

        fflush(stdout);
        
        //tested with output.txt
        //the filename must not have spaces
        removeChar(token,' ');
        removeChar(token,'\n');
        int f = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0666);//get file descriptor of file to open or generated one
        if(f==-1){                                              
            perror("open");
            exit(0);
        }
        //printf("2\n");
        //set the program to print to the file detailed or created
        int dupReturn = dup2(f,1);
        if(dupReturn==-1){
            perror("dup2");
            exit(0);
        }
        //printf("about to close f\n");
        close(f);
        //printf("3\n");
    }