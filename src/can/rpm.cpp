#include <globals.h>
#include <canbus.h>

const uint32_t CAN_BUS_ID = 0x0AA;

uint8_t rpmFrame[8] = {0x5F, 0x59, 0xFF, 0x00, 0x00, 0x00, 0x80, 0x99};

void sendRpm()
{
    uint16_t rpm = g_rpm * 4;

    rpmFrame[4] = rpm;
    rpmFrame[5] = (rpm >> 8);

    // Throttle (Byte 2 & 3)
    uint16_t throttleValue = map(g_throttle, 0, 100, 255, 65064);
    rpmFrame[2] = throttleValue & 0xFF;
    rpmFrame[3] = (throttleValue >> 8) & 0xFF;

    // Optionnel : Byte[7] pour refléter "pied posé ou pas"
    rpmFrame[7] = (g_throttle > 50) ? 0x80 : 0x94;

    CAN.sendMsgBuf(CAN_BUS_ID, 8, rpmFrame);
}