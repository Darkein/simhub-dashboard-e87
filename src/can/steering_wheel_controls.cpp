#include <globals.h>
#include <canbus.h>

void sendSteeringWheelControl(int button)
{
  uint8_t buttonFrame[2] = {0xC0, 0x0C};

  switch (button) {
    case 1: buttonFrame[1] = 0x1C; break;
    case 2: buttonFrame[1] = 0x4C; break;
  }

  CAN.sendMsgBuf(0x1D6, 0, 2, buttonFrame);
}