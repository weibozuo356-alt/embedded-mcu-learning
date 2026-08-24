#include <stdio.h>

int global_value = 5;

int calculate_result(int value, int offset);
void print_separator(void);

int main(void)
{
    int local_result = calculate_result(23, 5);

    printf("Function result: %d\n", local_result);
    printf("Global value: %d\n", global_value);
    print_separator();

    return 0;
}

int calculate_result(int value, int offset)
{
    value = value * 10;

    return value + offset;
}

void print_separator(void)
{
    printf("--------------------\n");
}
