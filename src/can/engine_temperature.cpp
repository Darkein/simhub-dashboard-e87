#include <globals.h>
#include <canbus.h>

const uint32_t CAN_BUS_ID = 0x1D0;

void sendEngineTemperature()
{
    const uint32_t ID = 0x1D0;
    static uint8_t frame[8] = {0x8B, 0xFF, 0x00, 0xCD, 0x00, 0x00, 0xCD, 0xA8};
    const uint8_t engine_run_state = g_ignition ? 0x2 : 0x0;  // 0x0 = off, 0x1 = starting, 0x2 = running, 0x3 = invalid
    static uint16_t fuel_injection_total = 0;

    frame[0] = g_water_temp + 48;

    // Update alive counter (lower 4 bits)
    static uint8_t alive_counter = 0;
    alive_counter = (alive_counter + 1) & 0x0F;

    // Encode engine_run_state into bits 4–5, preserve upper/lower bits
    frame[2] = alive_counter;
    frame[2] |= (engine_run_state & 0x03) << 4; // bits 4–5

    // Value is cumulative fuel injected in 100 ms cycles
    fuel_injection_total += g_fuel_injection;

    frame[4] = fuel_injection_total & 0xFF;
    frame[5] = (fuel_injection_total >> 8) & 0xFF;

    CAN.sendMsgBuf(CAN_BUS_ID, 8, frame);
}