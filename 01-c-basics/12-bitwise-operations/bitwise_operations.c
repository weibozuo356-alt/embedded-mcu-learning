#include <stdint.h>
#include <stdio.h>

#define BIT(position) (1U << (position))
#define MODE_POSITION 4U
#define MODE_MASK (3U << MODE_POSITION)

static void print_binary_u8(uint8_t value)
{
    for (int bit = 7; bit >= 0; --bit)
    {
        unsigned int current = ((unsigned int)value >> (unsigned int)bit) & 1U;
        printf("%u", current);

        if (bit == 4)
        {
            printf(" ");
        }
    }

    printf("\n");
}

static uint8_t set_mode(uint8_t register_value, uint8_t mode)
{
    uint8_t cleared_value = (uint8_t)(register_value & (uint8_t)(~MODE_MASK));
    uint8_t shifted_mode = (uint8_t)(((unsigned int)mode << MODE_POSITION) & MODE_MASK);

    return (uint8_t)(cleared_value | shifted_mode);
}

static uint8_t get_mode(uint8_t register_value)
{
    return (uint8_t)(((unsigned int)register_value & MODE_MASK) >> MODE_POSITION);
}

int main(void)
{
    uint8_t register_value = 0U;

    printf("Initial value:       ");
    print_binary_u8(register_value);

    register_value = (uint8_t)(register_value | BIT(3));
    printf("Set bit 3:           ");
    print_binary_u8(register_value);

    if ((register_value & BIT(3)) != 0U)
    {
        printf("Bit 3 is set.\n");
    }

    register_value = (uint8_t)(register_value & (uint8_t)(~BIT(3)));
    printf("Clear bit 3:         ");
    print_binary_u8(register_value);

    register_value = (uint8_t)(register_value ^ BIT(3));
    printf("Toggle bit 3:        ");
    print_binary_u8(register_value);

    register_value = set_mode(register_value, 2U);
    printf("Write mode 2:        ");
    print_binary_u8(register_value);
    printf("Read mode: %u\n", (unsigned int)get_mode(register_value));

    return 0;
}
