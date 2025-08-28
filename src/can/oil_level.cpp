#include <globals.h>
#include <canbus.h>

void sendOilLevel() {
    const uint32_t ID = 0x381;
    // min: 0x19
    // middle: 0x35
    const uint8_t level = 0x35;
    // >MAX: e.g. 0xF1
    // OK: 0xF0
    // +1l: 0xF2
    const uint8_t status = 0xF0;
    static uint8_t frame[8] = {level, status, 0xFF, 0, 0, 0, 0, 0};
    CAN.sendMsgBuf(ID, 8, frame);
}