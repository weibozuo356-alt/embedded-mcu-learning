#include <stdio.h>

static unsigned int module_counter = 0U;
static volatile unsigned int event_flag = 0U;

static unsigned int next_sequence(void)
{
    static unsigned int sequence = 0U;

    sequence++;
    module_counter++;
    return sequence;
}

static void simulate_external_event(void)
{
    event_flag = 1U;
}

int main(void)
{
    const unsigned int call_limit = 3U;
    int value = 10;
    int another_value = 20;
    const int *pointer_to_const = &value;
    int *const const_pointer = &value;

    printf("Read through pointer_to_const: %d\n", *pointer_to_const);
    pointer_to_const = &another_value;
    printf("After changing its target: %d\n", *pointer_to_const);

    *const_pointer = 15;
    printf("Value changed through const_pointer: %d\n", value);

    for (unsigned int index = 0U; index < call_limit; ++index)
    {
        printf("Sequence: %u\n", next_sequence());
    }

    printf("Module counter: %u\n", module_counter);

    simulate_external_event();

    if (event_flag != 0U)
    {
        printf("External event received.\n");
        event_flag = 0U;
    }

    return 0;
}
