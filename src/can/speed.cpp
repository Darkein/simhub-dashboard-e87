#include <globals.h>
#include <canbus.h>

const float speed_calibration = 240.0f / 230.0f;
void sendSpeed()
{
    /**
     * Default Speed
     */
    const uint32_t CAN_SPEED_COUNTER_ID = 0x1A6;
    uint8_t speedCounterFrame[8] = {0};
    static uint16_t speedCounterVal = 0; // 16-bit counter
    static uint32_t syncCounter = 0;     // compteur large pour bytes 6&7
    static unsigned long lastUpdate = 0;

    unsigned long now = millis();
    unsigned long dt = now - lastUpdate;

    // Envoie toutes les ~100 ms (ajuste si tu veux 200 ms)
    if (dt < 90)
        return; // anti-spam (évite d'envoyer plusieurs fois par boucle)
    if (dt > 1000)
        dt = 1000; // clamp pour éviter très grosses sauts (ex: wake after sleep)

    float mph = g_speed_mph * speed_calibration;

    // --- incrément des compteurs (formule spécifiée) ---
    // incr = (dt / 50ms) * speed_mph
    float factor = (float)dt / 50.0f;
    uint32_t incr = (uint32_t)round(factor * mph);

    // Mise à jour counter 16-bit (wrap automatique)
    speedCounterVal = (uint16_t)((uint32_t)speedCounterVal + (incr & 0xFFFF));

    // Écrire 3 copies (bytes 0..5)
    speedCounterFrame[0] = speedCounterVal & 0xFF;
    speedCounterFrame[1] = (speedCounterVal >> 8) & 0xFF;
    speedCounterFrame[2] = speedCounterFrame[0];
    speedCounterFrame[3] = speedCounterFrame[1];
    speedCounterFrame[4] = speedCounterFrame[0];
    speedCounterFrame[5] = speedCounterFrame[1];

    // --- compteur cyclique bytes 6&7 ---
    syncCounter += dt*4;
    speedCounterFrame[6] = syncCounter & 0xFF;
    speedCounterFrame[7] = (uint8_t)(0xF0 | ((syncCounter >> 8) & 0x0F)); // on peut garder full byte, cluster n'utilise que 4 LSB

    // Envoi CAN
    CAN.sendMsgBuf(CAN_SPEED_COUNTER_ID, 8, speedCounterFrame);

    // mise à jour timestamp après envoi
    lastUpdate = now;

    /**
     * wheels speed
     */
    const uint32_t CAN_SPEED_WHEEL_ID = 0x0CE;

    uint8_t wheelFrame[8] = {0};

    uint16_t wheelRaw = (uint16_t)(mph * 24);

    // 4 roues identiques
    wheelFrame[0] = wheelRaw & 0xFF;
    wheelFrame[1] = (wheelRaw >> 8) & 0xFF;
    wheelFrame[2] = wheelFrame[0];
    wheelFrame[3] = wheelFrame[1];
    wheelFrame[4] = wheelFrame[0];
    wheelFrame[5] = wheelFrame[1];
    wheelFrame[6] = wheelFrame[0];
    wheelFrame[7] = wheelFrame[1];

    CAN.sendMsgBuf(CAN_SPEED_WHEEL_ID, 8, wheelFrame);

    /**
     * Speed 0x1A1
     */
    const uint32_t CAN_SPEED_ID = 0x1A1;
    uint8_t speedFrame[5] = {0};

    // Encodage en "mph * 100"
    uint16_t rawSpeed = (uint16_t)(mph * 100.0f);

    // Byte0 et Byte1 = inutilisés
    speedFrame[0] = 0;
    speedFrame[1] = 0;

    // Byte2 & Byte3 = vitesse
    speedFrame[2] = rawSpeed & 0xFF;
    speedFrame[3] = (rawSpeed >> 8) & 0xFF;

    // Byte4 = non documenté → 0
    speedFrame[4] = 0;

    // Envoi CAN
    CAN.sendMsgBuf(CAN_SPEED_ID, 5, speedFrame);
}