#include <globals.h>
#include <canbus.h>
#include <lights.h>

void sendErrorLight(uint16_t light_id, bool enable)
{
    const uint32_t ID = 0x592;
    const uint8_t ON = 0x31;
    const uint8_t OFF = 0x30;

    uint8_t frame[] = {
        0x40,
        static_cast<uint8_t>(light_id & 0xFF),
        static_cast<uint8_t>((light_id >> 8) & 0xFF),
        enable ? ON : OFF,
        0xFF, 0xFF, 0xFF, 0xFF};
    CAN.sendMsgBuf(ID, 0, 8, frame);
}

void sendErrorLights()
{
    sendErrorLight(DSC_TRIANGLE_SYMBOL_ONLY, g_abs);
    sendErrorLight(DTC_SYMBOL_ONLY, g_tc);
    sendErrorLight(SERVICE_LIGHT, false);
    sendErrorLight(OIL_LEVEL_LOW, g_low_oil_pressure);
    sendErrorLight(CHECK_ENGINE_DOUBLE, g_check_engine);
    sendErrorLight(DOOR_OPEN_LEFT, g_door_open);
    sendErrorLight(CAR_AHEAD_YELLOW, g_car_ahead);

    if (g_low_pressure_front_left && g_low_pressure_front_right && g_low_pressure_rear_left && g_low_pressure_rear_right)
    {
        sendErrorLight(LOW_TIRE_PRESSURE_ALL, true);
    }
    else
    {
        sendErrorLight(LOW_TIRE_PRESSURE_ALL, false);
        sendErrorLight(LOW_TIRE_PRESSURE_FRONT_LEFT, g_low_pressure_front_left);
        sendErrorLight(LOW_TIRE_PRESSURE_FRONT_RIGHT, g_low_pressure_front_right);
        sendErrorLight(LOW_TIRE_PRESSURE_REAR_LEFT, g_low_pressure_rear_left);
        sendErrorLight(LOW_TIRE_PRESSURE_REAR_RIGHT, g_low_pressure_rear_right);
    }
}