#include <globals.h>
#include <canbus.h>

void sendSteeringWheel()
{
    const uint16_t CAN_ID = 0x0C4;
    uint8_t steering_wheel_frame[7] = {0x83, 0xFD, 0xFC, 0x00, 0x00, 0xFF, 0xF1};

    steering_wheel_frame[1] = 0;
    steering_wheel_frame[2] = 0;

    CAN.sendMsgBuf(CAN_ID, 7, steering_wheel_frame);
}

uint8_t epsCounterFrame[2] = {0xF0, 0xFF};
const uint16_t CAN_ID_EPS = 0x1fb;

void sendSteeringWheelEPS(){
    CAN.sendMsgBuf(CAN_ID_EPS, 2, epsCounterFrame);
    epsCounterFrame[1] = ((epsCounterFrame[1] + 1) | 0xF0);
}