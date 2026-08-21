#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 4

int main(void)
{
    int numbers[ARRAY_SIZE];

    printf("Enter %d integers: ", ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        scanf("%d", &numbers[i]);
    }

    printf("Original array: ");

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    /* Sort the array from largest to smallest using bubble sort. */
    for (int i = 0; i < ARRAY_SIZE - 1; i++)
    {
        for (int j = 0; j < ARRAY_SIZE - 1 - i; j++)
        {
            if (numbers[j] < numbers[j + 1])
            {
                int temporary = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temporary;
            }
        }
    }

    printf("Sorted array: ");

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    /* Store a string in a character array and copy another string into it. */
    char message[100] = "Hello, arrays!";
    strcpy(message, "C strings are character arrays.");
    printf("%s\n", message);

    return 0;
}
