#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 4
#define DYNAMIC_SIZE 5

void increase_value(int *value);
void write_message(char *destination);

int main(void)
{
    int numbers[ARRAY_SIZE] = {10, 20, 30, 40};
    int *pointer = numbers;

    printf("Pointer address: %p\n", (void *)pointer);
    printf("First value: %d\n", *pointer);

    pointer++;
    printf("Second value: %d\n", *pointer);

    increase_value(&numbers[0]);
    printf("Updated first value: %d\n", numbers[0]);

    char message[20];
    write_message(message);
    printf("Message: %s\n", message);

    int *dynamic_numbers = malloc(DYNAMIC_SIZE * sizeof(*dynamic_numbers));

    if (dynamic_numbers == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < DYNAMIC_SIZE; i++)
    {
        dynamic_numbers[i] = (i + 1) * 10;
        printf("dynamic_numbers[%d] = %d\n", i, dynamic_numbers[i]);
    }

    free(dynamic_numbers);
    dynamic_numbers = NULL;

    return 0;
}

void increase_value(int *value)
{
    *value = *value + 1;
}

void write_message(char *destination)
{
    strcpy(destination, "hello world");
}
