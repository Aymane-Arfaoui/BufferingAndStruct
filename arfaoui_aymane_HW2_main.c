/**************************************************************
* Class::  CSC-415-03 Spring 2024
* Name:: Aymane Arfaoui
* Student ID:: 923812458
* GitHub-Name::Aymane-Arfaoui
* Project:: Assignment 2 – Stucture in Memory and Buffering
*
* File:: arfaoui_aymane_HW2_main.c
*
* Description::
* Program that stores information in variables and
* commits sentences to a buffer
*
**************************************************************/
//assignment2.h contains our main functions and data
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"


int main(int argc, char *argv[]){


// Use dynamic memory allocation to allow variables to store 
// the name and last name which are part of the personalInfo Struct
struct personalInfo p1;
p1.firstName = malloc(strlen(argv[1])+1);
p1.lastName = malloc(strlen(argv[2])+1);
p1.studentID = 923812458;

// Make sure memory allocation is succesfull
if (p1.firstName == NULL || p1.lastName == NULL){
    fprintf(stderr,"Memory allocation failure :(");

    free(p1.firstName);
    free(p1.lastName);

    return 1;
}

strcpy(p1.firstName,argv[1]);
strcpy(p1.lastName,argv[2]);

//populate values for other variables, level and language.
p1.level = 18;

p1.languages = KNOWLEDGE_OF_C | KNOWLEDGE_OF_JAVA | KNOWLEDGE_OF_PYTHON | KNOWLEDGE_OF_INTEL_ASSEMBLER ;

//Deal with the message variable
strncpy(p1.message, argv[3], sizeof(p1.message)-1);
p1.message[sizeof(p1.message)-1]='\0';

int WriteInfo = writePersonalInfo(&p1);

printf("\n\n%d\n",WriteInfo);

//Allocate memory for the buffer that will contain our strings
char *buffer = malloc(BLOCK_SIZE);


const char *nextString = getNext();

//Keep track of how much we used the buffer (BufferUsed)
size_t bufferUsed = 0;

//Keep track of the length of each string (different from offsetString)
size_t strlength = strlen(nextString);

//Keep track of how much space is left in the remainder
size_t remainder = BLOCK_SIZE;

//Keep track of how much of the string has been put in the buffer before a commit,
// so we can know where to start copying from again once the buffer is commited.
size_t offsetString = 0;

//As long as the string is not null...
while(nextString){
    strlength = strlen(nextString);
    // While loop that deals with case #1 where the string length is bigger than 
    // what is left in the buffer by keeping track of the index we coppied 
    // (using memcpy) and the length remaining in the buffer.
    while(strlength > remainder){        
        memcpy(buffer+bufferUsed, nextString+offsetString, remainder);
        //Update the index of where we left off on the string  
        offsetString += remainder;
    
        strlength -= remainder;

        bufferUsed = 0;
        remainder = BLOCK_SIZE - bufferUsed;
        commitBlock(buffer);
        
    }
    //once the loop is done, we fall into the case where remainder is bigge
    // this case is similar to the exact last step remaining after the while loop 
    // before is done. which is why the following block of code is at the end
    if(remainder > strlength){
        memcpy(buffer+bufferUsed,nextString + offsetString,strlength);
        bufferUsed += strlength;
        remainder = BLOCK_SIZE - bufferUsed;
    }
     nextString = getNext();
     offsetString = 0;

}

commitBlock(buffer);
free(buffer);
int check = checkIt();
}