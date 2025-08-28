#include <globals.h>
#include <canbus.h>

void sendVehicleDynamics()
{
    const uint32_t ID = 0x1A0;
    static uint8_t alive_counter = 0;

    float speed_kmh = g_speed / 10.f;
    // Moving forward, backward not supported yet
    uint8_t st_veh_dvco = speed_kmh >= 1 ? 1 : 0;
    float acc_long = 0.f; // m/s²
    float acc_lat = 0.f;  // m/s²
    float yaw_rate = 0.f; // deg/s

    uint16_t v_veh_raw = (uint16_t)(speed_kmh / 0.1f);
    int16_t acc_long_raw = (int16_t)(acc_long / 0.025f);
    int16_t acc_lat_raw = (int16_t)(acc_lat / 0.025f);
    int16_t yaw_rate_raw = (int16_t)(yaw_rate / 0.05f);

    uint8_t frame[8] = {0};

    frame[0] = v_veh_raw & 0xFF;
    frame[1] = (st_veh_dvco & 0x07) << 4;
    frame[2] = acc_long_raw & 0xFF;
    frame[3] = ((acc_long_raw >> 8) & 0x0F) | ((acc_lat_raw & 0x0F) << 4);
    frame[4] = (acc_lat_raw >> 4) & 0xFF;
    frame[5] = yaw_rate_raw & 0xFF;
    frame[6] = ((yaw_rate_raw >> 8) & 0x0F) | ((alive_counter++ & 0x0F) << 4);

    uint8_t checksum = 0x00;
    for (int i = 0; i < 7; i++)
    {
        checksum ^= frame[i];
    }
    frame[7] = checksum;

    CAN.sendMsgBuf(ID, 8, frame);
}