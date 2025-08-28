#include <globals.h>
#include <canbus.h>

const uint32_t CAN_BUS_ID = 0x1A6;

uint8_t speedFrame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0};

uint16_t lastSpeed = 0;

void sendSpeed()
{
    const uint32_t ID = 0x1A6;
    static uint16_t last_speed_counter = 0;
    static uint16_t last_tick_counter = 0;
    uint32_t delta_ms = 100;
    uint16_t speed_mph = g_speed * 0.621371f;
    uint16_t current_speed_counter = speed_mph + last_speed_counter;
    uint16_t delta_tick_counter = delta_ms * 2;
    uint16_t tick_counter = last_tick_counter + delta_tick_counter;

    uint8_t low = current_speed_counter & 0xFF;
    uint8_t high = current_speed_counter >> 8;

    uint8_t frame[8] = {
        low, high,
        low, high,
        low, high,
        (uint8_t)(tick_counter & 0xFF),
        (uint8_t)(0xF0 | ((tick_counter >> 8) & 0x0F))
    };

    CAN.sendMsgBuf(ID, 8, frame);
    last_speed_counter = current_speed_counter;
    last_tick_counter = tick_counter;

    const uint32_t CAN_SPEED_ID = 0x0CE;

    uint8_t wheelFrame[8] = {0};

    // Conversion km/h -> mph
    float mph = g_speed * 0.621371f;
    uint16_t wheelRaw = (uint16_t)(mph * 24);

    // 4 roues identiques
    wheelFrame[0] = wheelRaw & 0xFF;
    wheelFrame[1] = (wheelRaw >> 8) & 0xFF;
    wheelFrame[2] = wheelFrame[0];
    wheelFrame[3] = wheelFrame[1];
    wheelFrame[4] = wheelFrame[0];
    wheelFrame[5] = wheelFrame[1];
    wheelFrame[6] = wheelFrame[0];
    wheelFrame[7] = wheelFrame[1];

    CAN.sendMsgBuf(CAN_SPEED_ID, 8, wheelFrame);
}