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
    sendErrorLight(CRUISE_WARNING, false);
    sendErrorLight(STEERING_WARNING, false);
}