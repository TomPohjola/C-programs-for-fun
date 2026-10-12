#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <stdbool.h>

int *createArr(int n);
int binarySearchAlg(int *array, int key, int low, int high, unsigned long long threadId, bool *numberFound);

#endif // BINARYSEARCH_H
