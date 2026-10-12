#include <stdio.h>
#include "pointerArith.h"
#include <pthread.h>
#include <stdbool.h>

int main()
{
    float op1 =0, op2 =0, sum =0;
    int progSelect, searchedNumber;
    char inputBuf[100];

    do
    {
        printf("select program. 1 = pointer arithmetics, 2 = sum two numbers with pointers, \n");
        printf("3 = create an array of one million elements and use 4 threads to binary search your number, 5 = exit\n");
        while (fgets(inputBuf, sizeof(inputBuf), stdin))
        {
            if (sscanf(inputBuf, "%d", &progSelect) == 1) break;
            else
            {
                printf("Invalid input. Try again: ");
            }
        }

        switch (progSelect) {
        case 1:
            pointerArith();
            break;
        case 2:

            printf("give first operand:\n");
            scanf("%f", &op1);
            printf("give second operand:\n");
            scanf("%f", &op2);

            sum = sumNums(&op1,&op2);

            printf("sum of the operands are: %0.2f\n", sum);
            break;
        case 3:
            printf("give a number to look for in range of 0-1,000,0000:\n");
            while (fgets(inputBuf, sizeof(inputBuf), stdin))
            {
                //if (sscanf(inputBuf, "%d", &key) == 1 && (key > 0 && key <= 1000000)) break;
                if (sscanf(inputBuf, "%d", &searchedNumber) == 1) break;
                else
                {
                    printf("Invalid input. Try again!\n");
                }
            }

            MultiThreadBinarySearch(4, searchedNumber); //annetaan säikeiden lkm tällä. toistaiseksi kovakoodattu 4 säiettä.
            break;
        case 5:
            printf("End of main program!\n");
            break;
        default:
            printf("Select a valid program!\n");
            break;
        }
    }
    while(progSelect != 5);

    return 0;
}
