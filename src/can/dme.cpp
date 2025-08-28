#include <globals.h>
#include <canbus.h>

void sendDmeStatus() {
    const uint32_t ID = 0x12F;
    uint8_t frame[8] = {0x3F, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00};
    CAN.sendMsgBuf(ID, 8, frame);
}