#include "headers.h"
//#include <config.h>//for automake

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
/*
By:
Cesar Rondo Rodriguez
email: c.rondoro12@gmail.com
*/


int main(){

    int exitProg=0;
    int runCmd; //variable to know if a command has been called correctly
    char *buff;
    size_t buffSize=0;
    int inputSize=0;

    pid_t childID;//id of the child process that will run the inputed commands
    int execSuccess=0;//integer that will indicate if the commands were executed successfully
    int tempIndex; //integer used to temporarily store data (array indexes) for each iteration of the loop


    int stdout_fileDescriptor = dup(STDOUT_FILENO);


    if(signal(SIGINT,signalHandler)==SIG_ERR){
        printf("signal handler could not be set up\n");
    }

    while(exitProg==0){

        
        runCmd=1;
        printTime();
        printf("# ");

        //scan whole line
        getline(&buff,&buffSize,stdin);
        removeChar(buff,'\n');
        //printf("Input <%s>, has length %ld in bytes\n", buff,sizeof(buff));
        //when user presses Ctrl+D stdin receives EOF
        if(feof(stdin)){
            exitProg=1;
            break;
        }

        tempIndex=findRedirect(buff,strlen(buff));
        //printf("tempIndex: %d\n", tempIndex);
        if(tempIndex>0){//check for > and if found redirects to the file specified
            redirect(buff);
        }
        inputSize=strlen(buff);
        //printf("buffLen=%d\n",inputSize);
        char *command = getCommand(buff, inputSize); //command called by the user, created and freed each loop because is dynamically allocated
        if(command==NULL){
            runCmd=0; //nothing was called, user only pressed \n
        }
        //printf("Command called is <%s>\n",command);
        char ** argArr=getArguments(buff,inputSize);//generate the arguments of the call
        if(command!=NULL && strcmp(command,"cd")==0){//called cd
            //printf("cd recognised\n");
            runCmd=0;
            handleCD(argArr);
        }

        if(runCmd==1){
            execSuccess=runCommand(command,argArr);
        }


        free(command); //free command as it was dynamically allocated when generated in its function
        free(argArr); //free the argument array as it was dynamically allocated when generated in its function
        //printf("variables freed\n");
        //printf("tempIndex: %d\n", tempIndex);
        if(tempIndex>=1){
            //printf("closing file\n");
            //close(1);
            //int temp_stdout_fileDescriptor = dup(stdout_fileDescriptor);
            int use_stdout = dup2(stdout_fileDescriptor,1);
            printf("file closed\n");
        }
    }
    printf("\n");

    return 0;
}

