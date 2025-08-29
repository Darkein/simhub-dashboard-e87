#include <globals.h>
#include <canbus.h>

void sendSteeringWheel()
{
    const uint16_t CAN_ID = 0x0C4;
    uint8_t steering_wheel_frame[7] = {0x83, 0xFD, 0xFC, 0x00, 0x00, 0xFF, 0xF1};

    steering_wheel_frame[1] = 0;
    steering_wheel_frame[2] = 0;

    CAN.sendMsgBuf(CAN_ID, 7, steering_wheel_frame);

    const uint16_t CAN_ID_EPS = 0x1fb;
    uint8_t eps_frame[8] = {0};
    CAN.sendMsgBuf(CAN_ID_EPS, 8, eps_frame);
}

void sendSteeringWheelSlow()
{
    float angleDeg = 0;
    float speedDegPerSec = 0;

    const uint16_t CAN_ID = 0x0C8;
    uint8_t frame[6] = {0};

    // SteeringPosition (0..15)
    int16_t angleRaw = angleDeg / 0.04395f;
    frame[0] = (angleRaw >> 8) & 0xFF;
    frame[1] = angleRaw & 0xFF;

    // Counter 0xC8 (bits 20–23 → octet 2, high nibble)
    static uint8_t counter_c8 = 0;
    frame[2] = (counter_c8 & 0x0F) << 4;
    counter_c8 = (counter_c8 + 1) & 0x0F;

    // SteeringSpeed (24..39)
    int16_t speedRaw = speedDegPerSec / 0.04395f;
    frame[3] = (speedRaw >> 8) & 0xFF;
    frame[4] = speedRaw & 0xFF;

    // Octet 5 inutilisé
    frame[5] = 0;

    CAN.sendMsgBuf(CAN_ID, 0, 6, frame);
}

void sendSteeringWheelDSC()
{

    const uint16_t CAN_ID = 0x392;
    uint8_t frame[8] = {0};

    // === SteeringPosition ===
    float angleDeg = 0.0;                  // angle à simuler
    int16_t angleRaw = angleDeg / 0.04395; // conversion DBC
    frame[0] = (angleRaw >> 8) & 0xFF;     // MSB
    frame[1] = angleRaw & 0xFF;            // LSB

    // === Counter 0xC9 ===
    static uint8_t counter = 0;
    frame[2] = (counter & 0x0F) << 4; // bits 20-23
    counter = (counter + 1) & 0x0F;

    // === SteeringPositionComplementLow ===
    // 11 bits à partir du bit 24
    uint16_t complement = 0;             // on peut laisser 0 pour test
    frame[3] = (complement >> 3) & 0xFF; // bits 24-31
    frame[4] = (complement & 0x07) << 5; // bits 32-34, reste à 0

    // Les octets restants peuvent rester à 0
    frame[5] = 0;
    frame[6] = 0;
    frame[7] = 0;

    CAN.sendMsgBuf(CAN_ID, 0, 8, frame);
}