#include <canbus.h>

uint32_t previous = 0;
uint32_t counter = 0;

void sendCanBus()
{
    uint32_t current = millis();
    if (current - previous >= 10)
    {
        sendIgnition();
        sendErrorLights();

        if (counter % 10 == 0)
        {
            sendSteeringWheel();
        }

        if (counter % 20 == 7)
        {
            sendSpeed();
            sendRpm();
            sendAbs();
            sendLightning();
            sendAirbag();
            sendEngineTemperature();
            sendFuel();
            sendHandbrake();
            sendSeatbelt();
            sendIndicators();
        }

        if (counter % 50 == 0)
        {
        }

        if (counter % 100 == 0)
        {
            sendTime();
        }

        counter++;
        previous = current;
    }
}
