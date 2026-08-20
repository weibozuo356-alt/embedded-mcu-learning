#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num = 21;
    int input = 0;

    while (1)
    {
        printf("Please enter a number: ");
        scanf("%d", &input);

        /* This Windows command works when the program runs in a real terminal. */
        system("cls");

        if (input < num)
        {
            printf("Too low!\n");
        }
        else if (input > num)
        {
            printf("Too high!\n");
        }
        else
        {
            printf("Correct!\n");
            break;
        }
    }

    return 0;
}
