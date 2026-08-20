#include <stdio.h>

int main(void)
{
    int i = 0;

    /* Use a while loop to print the numbers from 0 to 66. */
    while (i < 67)
    {
        printf("%d\n", i);
        i++;
    }

    /* Use a for loop to print the same range. */
    for (int j = 0; j < 67; j++)
    {
        printf("%d\n", j);
    }

    /* Keep reading numbers until the input is 251 or greater. */
    while (1)
    {
        int number;

        printf("Enter a number: ");
        scanf("%d", &number);

        if (number < 251)
        {
            printf("%d\n", number);
        }
        else
        {
            break;
        }
    }

    return 0;
}
