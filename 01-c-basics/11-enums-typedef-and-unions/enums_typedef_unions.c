#include <stdint.h>
#include <stdio.h>

typedef enum
{
    LED_OFF = 0,
    LED_ON,
    LED_BLINKING
} LedState;

typedef struct
{
    const char *name;
    uint16_t value;
    LedState state;
} Sensor;

typedef union
{
    uint32_t word;
    uint8_t bytes[4];
} SharedData;

static const char *led_state_name(LedState state)
{
    switch (state)
    {
        case LED_OFF:
            return "off";
        case LED_ON:
            return "on";
        case LED_BLINKING:
            return "blinking";
        default:
            return "unknown";
    }
}

int main(void)
{
    Sensor temperature_sensor = {"temperature", 235U, LED_ON};
    SharedData data = {0};

    printf("Sensor name: %s\n", temperature_sensor.name);
    printf("Sensor value: %u\n", (unsigned int)temperature_sensor.value);
    printf("LED state: %s\n", led_state_name(temperature_sensor.state));

    data.word = UINT32_C(0x12345678);
    printf("\nStored word: 0x%08lX\n", (unsigned long)data.word);
    printf("Union size: %zu bytes\n", sizeof(data));
    printf("Address of word:  %p\n", (void *)&data.word);
    printf("Address of bytes: %p\n", (void *)&data.bytes[0]);

    data.bytes[0] = UINT8_C(0xAA);
    printf("Current byte value: 0x%02X\n", (unsigned int)data.bytes[0]);

    return 0;
}
