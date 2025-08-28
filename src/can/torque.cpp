#include <globals.h>
#include <canbus.h>

const uint32_t CAN_TORQUE_ID = 0x0A8;
uint8_t torqueFrame[8] = {0};

void sendTorque()
{
    uint16_t maxTorque = 7000.0f;
    const bool g_clutch = false;
    const bool g_brake = false;

    if (g_max_torque > 100)
    {
        maxTorque = g_max_torque;
    }
    // --- Calcul du couple à partir du régime ---
    float torqueNm = (g_rpm / maxTorque) * 400.0f; // simplifié
    int16_t rawTorque = (int16_t)(torqueNm * 32);  // 2’s complement

    // Bytes 0–1 = Torque complet
    torqueFrame[0] = rawTorque & 0xFF;
    torqueFrame[1] = (rawTorque >> 8) & 0xFF;

    // Bytes 2–3 = Torque arrondi
    int16_t roundedRaw = (int16_t)(((int)torqueNm) * 32);
    torqueFrame[2] = roundedRaw & 0xFF;
    torqueFrame[3] = (roundedRaw >> 8) & 0xFF;

    // Byte 4 = Clutch
    torqueFrame[4] = g_clutch ? 0xF1 : 0xF0;

    // Byte 5 = inutilisé → 0
    torqueFrame[5] = 0;

    // Byte 6 = Brake
    torqueFrame[6] = g_brake ? 63 : 0;

    // Byte 7 = toujours 0
    torqueFrame[7] = 0;

    // Envoi CAN
    CAN.sendMsgBuf(CAN_TORQUE_ID, 8, torqueFrame);
}
