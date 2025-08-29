#include <globals.h>
#include <canbus.h>


uint8_t counterGear = 0x0;

int mapGenericGearToLocalGear(GearState inputGear) {
  // The gear that the car is in: 0 = clear, 1-9 = M1-M9, 10 = P, 11 = R, 12 = N, 13 = D

  switch(inputGear) {
    case GearState_Manual_1: return 0x78; break;
    case GearState_Manual_2: return 0x78; break;
    case GearState_Manual_3: return 0x78; break;
    case GearState_Manual_4: return 0x78; break;
    case GearState_Manual_5: return 0x78; break;
    case GearState_Manual_6: return 0x78; break;
    case GearState_Manual_7: return 0x78; break;
    case GearState_Manual_8: return 0x78; break;
    case GearState_Manual_9: return 0x78; break;
    case GearState_Manual_10: return 0x78; break;
    case GearState_Auto_P: return 0xE1; break;
    case GearState_Auto_R: return 0xD2; break;
    case GearState_Auto_N: return 0x87; break;
    case GearState_Auto_D: return 0x78; break;
    case GearState_Auto_S: return 0x78; break;
    default: return 0;
  }
}

void sendGearStatus() {
  // 0xE1, C3 = P
  // 0xD2 = R
  // 0xF0 = Clear
  // 0x78 = D
  // 0x87, 0x96 = N
  int gear = mapGenericGearToLocalGear(g_gear);
  uint8_t gearFrame[6] = {(uint8_t)gear, 0x0C, 0x80, (uint8_t)(counterGear << 4 | 0x0C), 0xF0, 0xFF};
  CAN.sendMsgBuf(0x1D2, 0, 6, gearFrame);

  counterGear++;
  if (counterGear > 15) {
    counterGear = 0;
  }
}