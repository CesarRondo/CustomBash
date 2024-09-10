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
#include <time.h>


char *getCommand (char *buffer, int buffLen){ 
    //function to get the first word of the scanned line, which will be in this simple shell, the command
    //this function also covers the cases where the user inputs nothing or just spaces
    if(buffer==NULL || buffLen==0){
        return NULL;
    }
    
    char c=buffer[0];
    int i=0;
    while(c==' '){
        i++;
        c=buffer[i];
        if(c=='\0'){
            return NULL;
        }
    }

    //create a loop that counts until the index of the first ' '
    int j=i; //set index j to where the first word starts

    while(c!=' ' && c!='\n' && c!='\0'){ //set index i to where the first index ends
        c = buffer[i];
        i++;
    }

    //store contents of the first word into command using the obtainded index
    char *command= (char*)malloc(i*sizeof(char)) ;
    for(j;j<i;j++){
        command[j]=buffer[j];
    }
    command[i]='\0';
    removeChar(command,' ');
    return command;
    
}




char** getArguments (char *buffer,int buffLen){ //function to get the arguments of the program call using tokens

    char* token=strtok(buffer," "); //skip the first token cause its the command
    if(token == NULL){
        return NULL;
    }
    char** argumentArr=malloc(1*sizeof(char*)); //create a dynamically allocated array of strings that will contain the arguments
    int arrSize=0;//max index, not size 
    //argumentArr[0]=token;
    argumentArr[arrSize]=token; //store current token into the argumentArray
    while (token!=NULL){
        token=strtok(NULL," ");
        arrSize++;
        if(arrSize>=1){
            argumentArr=realloc(argumentArr,(arrSize+1)*sizeof(char*));//increase size of array by 1
        }
        argumentArr[arrSize]=token; //store current token into the argumentArray
    }

    /*
    if(arrSize!=0){
            argumentArr=realloc(argumentArr,(arrSize+2)*sizeof(char*));//add 1 last string which will be NULL
    }
    argumentArr[arrSize+2]=NULL;

    */

    return argumentArr;         //return the array of arguments
}


void removeChar(char *str, char c) { //Helper function to remove characters, useful to remove spaces or \n
    int len = strlen(str);
    int i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; 
}

void printTime(){

    //get time in tm struct format
    time_t rawtime; 
    rawtime=time(NULL);
    struct tm* info;
    info = localtime(&rawtime);

    //create a string containing the necessary parts of the current time
    char buffer[10];
    char temp[10];
    char final[20];
    final[0]='[';
    final[1]='\0';
    sprintf(buffer,"%d",info->tm_mday);  //add the day to the time
    if((info->tm_mday)<10){
        strcpy(temp,"0");
        strcat(temp,buffer);
        strcpy(buffer,temp);
    }
    strcat(final,buffer);
    strcat(final,"/");


    sprintf(buffer,"%d",(info->tm_mon)+1);  //add the month to the time
    if((info->tm_mon)<10){
        strcpy(temp,"0");
        strcat(temp,buffer);
        strcpy(buffer,temp);
    }
    strcat(final,buffer);
    strcat(final," | ");


    sprintf(buffer,"%d",info->tm_hour);  //add the hour to the time
    if((info->tm_hour)<10){
        strcpy(temp,"0");
        strcat(temp,buffer);
        strcpy(buffer,temp);
    }
    strcat(final,buffer);
    strcat(final,":");


    sprintf(buffer,"%d",info->tm_min);  //add the minutes to the time
    if((info->tm_min)<10){
        strcpy(temp,"0");
        strcat(temp,buffer);
        strcpy(buffer,temp);
    }
    strcat(final,buffer);
    strcat(final,"]");

    printf("%s", final);
}
