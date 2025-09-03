#include <globals.h>
#include <canbus.h>

const uint32_t CAN_BUS_ID = 0x1D0;
const float fuel_density = 0.745f; // essence kg/L
const float scaling_factor = 1.300f;      // trouvé empiriquement pour corriger l’écart

void sendEngineTempAndFuelInjection()
{
    static uint8_t frame[8] = {0x8B, 0xFF, 0x00, 0xCD, 0x00, 0x00, 0xCC, 0xA8};
    const uint8_t engine_run_state = g_ignition ? 0x2 : 0x0; // 0x0 = off, 0x1 = starting, 0x2 = running, 0x3 = invalid
    static uint16_t fuel_injection_total = 0;
    static unsigned long lastUpdate = 0;
    
    unsigned long now = micros();
    unsigned long dt = now - lastUpdate;


    frame[0] = g_water_temp + 48;
    frame[1] = g_oil_temp;

    // Update alive counter (lower 4 bits)
    static uint8_t alive_counter = 0;
    alive_counter = (alive_counter + 1) & 0x0F;

    // Encode engine_run_state into bits 4–5, preserve upper/lower bits
    frame[2] = alive_counter;
    frame[2] |= (engine_run_state & 0x03) << 4; // bits 4–5

    if (g_speed_kph > 0 && g_l_100km > 0)
    {
        float L_h = (g_l_100km * g_speed_kph) / 100.0f;
        float mg = (L_h / 3600.0f) * fuel_density * (dt);
        fuel_injection_total += (uint16_t)(mg * scaling_factor);
    }

    frame[4] = fuel_injection_total & 0xFF;
    frame[5] = (fuel_injection_total >> 8) & 0xFF;

    CAN.sendMsgBuf(CAN_BUS_ID, 8, frame);
    
    // mise à jour timestamp après envoi
    lastUpdate = now;
}