#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include<windows.h>
#include <stdbool.h>
#include "binarysearch.h"

enum indexRanges
{
    arrSize = 1000000,
    randomGenRange = 1000000,
    indexIncrement = 250000
};

struct threadTimes
{
    int id;
    int time;
};
struct GeneratedArray
{
    int elements[arrSize];
    int *arrPointer;
    int randomIndex;
    int searchedNumber;
    int numOfThreads;
};

void fillElements(int elements[])
{
    for(int it = 0; it <= arrSize; it++)
    {
        elements[it] = it*10;
    };
}

bool numberFound = false, incremented = false;
bool *ptrToBool = &numberFound;
struct GeneratedArray gA;
pthread_mutex_t lock; //mutex lukko suojaamaan säikeiden kriittinen alue
int start = 0, end = indexIncrement; //indeksi alue

//-------------------------- //vanha versio demonstroimaan monisäikeistä ajoa. käy läpi iteratiivisesti taulukon alkiota läpi jollakin indeksialueella.
void* threadFunctionForIterativeSearch(void *received_struct)
{
    pthread_t thisThread = pthread_self();
    bool incremented = false;
    struct GeneratedArray *my_gAPointer = (struct GeneratedArray*) received_struct;

    pthread_mutex_lock(&lock);

    printf("thread ID %lu start index is: %d and end index is: %d\n",(unsigned long)thisThread, start, end);
    for(int i = start; i <= end; i++)
    {
        printf("thread ID %lu searchining from index %d...\n",(unsigned long)thisThread, i);
        if(numberFound)
        {
            printf("element found by another thread!\n");
            pthread_exit(NULL);
        }
        if(!incremented)
        {
            printf("incrementing search area!\n");
            start = start+indexIncrement;
            end = end+indexIncrement;
            incremented = true;
            pthread_mutex_unlock(&lock);
        }
        if(i == my_gAPointer->randomIndex)
        {
            numberFound = true;
            printf("element found from index %d, found by thread ID %lu, its value is: %d\n",i,(unsigned long)thisThread,gA.elements[i]);
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}
//----------------------------

void* threadFuncForBinarySearch(void *received_struct) // säiefunktio, mikä tekee binäärihaun taulukosta jollakin indeksialueella.
{
    pthread_mutex_lock(&lock); //vältetään race conditionit mutexi lukolla. käytetään säikeessä aina lokaalia starttia ja endiä, ja päivitetään globaalit startit ja endit

    pthread_t thisThread = pthread_self();
    int localStart = start, localEnd = end;
    bool incremented = false;
    struct GeneratedArray *my_gAPointer = (struct GeneratedArray*) received_struct;
    if(!incremented)
    {
        start = start+indexIncrement;
        end = end+indexIncrement;
        incremented = true;
    }
    pthread_mutex_unlock(&lock);

    int result = binarySearchAlg(my_gAPointer->arrPointer, my_gAPointer->searchedNumber, localStart, localEnd, thisThread, ptrToBool);

    pthread_exit(NULL);
}

void MultiThreadBinarySearch(int numOfThreads, int searchedNumber)
{   
    srand(time(NULL));
    gA.arrPointer = createArr(arrSize); //luodaan tässä dynaamisesti array ja osoitin siihen
    gA.searchedNumber = searchedNumber;
    gA.numOfThreads = numOfThreads;

    pthread_t arrayOfThreads[numOfThreads]; //luodaan numOfThreadsin mukainen määrä säikeitä taulukkoon
    int counter = 0;

    for(int i = 0; i < numOfThreads; i++)
    {
        if(numberFound) //keskeytetään säikeiden luonti jos joku säie on jo löytänyt luvun.
        {
            printf("NUMBER FOUND. TERMINATING THREAD CREATION\n", i);
            printf("\n");
            break;
        }
        else if(pthread_create(&arrayOfThreads[i], NULL, threadFuncForBinarySearch, (void *)&gA) != 0 )
        {
            printf("Error creating thread %d!\n", arrayOfThreads[i]);
        }
        else printf("Created thread %d!\n", arrayOfThreads[i]);
        counter++;
    }

    for (int i = 0; i < counter; i++)  //ja odotellaan niiden valmistuminen.
    {
        pthread_join(arrayOfThreads[i], NULL);
        printf("Thread number %lu finished\n", arrayOfThreads[i]);
    }

    numberFound = false; //resetoidaan muuttujat
    start = 0;
    end = indexIncrement;
    free(gA.arrPointer);
}

float sumNums(float *op1, float *op2)
{
    printf("the value of given operands are: %0.2f and %0.2f\n", *op1, *op2);
    return *op1 + *op2;
}

void pointerArith()
{
    int valueArray[10] = {1,2,3,4,5,6,7,8,9,10};
    int *pointer = valueArray;
    int input;
    char inputBuf[100], str[2], strOptions[4][4] = {"st", "nd", "rd", "th"};

    printf("This program is an exercise of pointer arithmetics.\nAccessing elements in an array is done by adding the size of integer type into the memory address.\n");
    printf("Normally this is done by using indeces, which is an implementation of the same operation done in more human-readable way.\n\n");
    do
    {
        printf("You have an array of 10 items, ranging from 1-10. which item would you like to view? Select from 1 to 10.\n");
        printf("to exit, enter 99.\n");

        while (fgets(inputBuf, sizeof(inputBuf), stdin))
        {
            if (sscanf(inputBuf, "%d", &input) == 1) break;
            else
            {
                printf("Invalid input. Try again: ");
            }
        }

        if(input == 99) printf("End of program!\n");
        else if (input < 1 | input > 10) printf("select a valid option!\n");
        else
        {
            switch (input) {
            case 1:
                strcpy(str, strOptions[0]);
                break;
            case 2:
                strcpy(str, strOptions[1]);
                break;
            case 3:
                strcpy(str, strOptions[2]);
                break;
            default:
                strcpy(str, strOptions[3]);
                break;
            }

            pointer = pointer+input-1;
            printf("you've chosen the %d%s element of the array, and its memory address is: %p and its value is: %d\n", input, str, pointer, pointer[0]);
            pointer = valueArray;
        }
    }
    while(input != 99);
};
