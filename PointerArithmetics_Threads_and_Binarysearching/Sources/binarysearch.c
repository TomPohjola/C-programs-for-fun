#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int *createArr(int n)
{
    srand(time(NULL));
    int random = 0, currentValue = 0, min = 3, max = 10;
    int* array = (int*)malloc(n * sizeof(int));
    array[0] = 0;

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 1; i < n; i++)
    {
        currentValue = array[i-1];
        random = rand() % (max - min + 1) + min; //random luku alueella min-max. luodaan sortattu taulukko, mutta ei täysin lineaarisesti kasvava
        array[i] = currentValue+random;       
    }

    return array;
}

int binarySearchAlg(int *array, int searchedNumber, int low, int high, unsigned long long threadId, bool *numberFound)
{

    int midIndex = (low+high)/2, previousNumber = 0, iterations = 0;
    printf("id %lu Thread start index = %d and end index = %d\n", threadId, low, high);

    while(midIndex != previousNumber)
    {
        if(*numberFound)
        {
            printf("NUMBER FOUND BY ANOTHER THREAD\n");
            return 0;
        }
        if(array[midIndex] == searchedNumber)
        {
            printf("NUMBER %d FOUND IN INDEX %d\n",array[midIndex], midIndex);
            printf("\n");
            *numberFound = true;
            return 0;
        }

        previousNumber = midIndex;

        printf("Mid key/index is: %d, its value is: %d and searched number %d\n", midIndex,array[midIndex], searchedNumber);

        if(searchedNumber < array[midIndex])
        {
            high = midIndex;
            midIndex = (low+high)/2;
        }
        if(searchedNumber > array[midIndex])
        {
            low = midIndex;
            midIndex = (low+high)/2;
        }
        iterations++;
        if(iterations > 100) break;
    }
    printf("NUMBER NOT PRESENT IN ARRAY RANGE. ITERARIONS: %d\n", iterations);
    printf("\n");
    return 0;
}
