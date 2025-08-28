#include <globals.h>
#include <canbus.h>

inline uint8_t getCruiseTimer(uint16_t call_interval_ms = 100, int shift = 0)
{
    static uint8_t timer = 0;
    static uint16_t ms_accumulator = 0;

    const uint16_t TIMER_INTERVAL_MS = 200;
    const uint8_t TIMER_STEP = 17;

    ms_accumulator += call_interval_ms;
    if (ms_accumulator >= TIMER_INTERVAL_MS)
    {
        ms_accumulator = 0;
        timer = (timer + TIMER_STEP + shift) % 256;
    }

    return timer;
}

void sendCruiseControl()
{
    const uint32_t ID = 0x193;

    static uint8_t last_kmh = 0xFE;
    static bool last_enabled = false;

    uint8_t kmh = g_cruise_enabled ? min(g_cruise_speed, (uint16_t)250) : 0xFE;
    uint8_t cruise_status = g_cruise_enabled ? 0xF4 : 0xF1; // 0xF5 for mph!
    uint8_t cc_flag = g_cruise_enabled ? 0x58 : 0x50;
    uint8_t speed_update = (kmh != last_kmh || g_cruise_enabled != last_enabled) ? 0x01 : 0x00;

    last_kmh = kmh;
    last_enabled = g_cruise_enabled;

    uint8_t frame[8] = {
        getCruiseTimer(100),
        kmh,
        cruise_status,
        0x00,
        0xF8,
        cc_flag,
        speed_update,
        0x00};
    ;
    CAN.sendMsgBuf(ID, 8, frame);

    byte data[8] = {0};

    data[0] = g_cruise_speed*10;

    // Flags Active/Inactive
    // bits 12 = Inactive, 13 = Active (dans octet 1, bit 4 et 5 si counting bits à partir de LSB)
    data[1] = 0; // initialisation
    if(g_cruise_enabled) {
        data[1] |= (1 << (13-8)); // bit 13 → 5ème bit du byte1
    } else {
        data[1] |= (1 << (12-8)); // bit 12 → 4ème bit du byte1
    }

    CAN.sendMsgBuf(0x200, 8, data);
}