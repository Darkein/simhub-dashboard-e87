#include <canbus.h>
#include <globals.h>

uint32_t previous = 0;
uint32_t counter = 0;

void sendCanBus()
{
    uint32_t now_us = micros();
    uint32_t current = now_us / 1000;
    if (current - previous >= 10)
    {

        if (counter % 10 == 0)
        {
            sendIgnition();
            sendGearStatus();
            sendSteeringWheelFast();
            sendSpeed();
            sendDmeStatus();
            sendCruiseControl();
            sendVehicleDynamics();
        }
        
        // Send every 50 ms
        if (counter % 5 == 1) {
            sendRpm();
            sendErrorLights();
            sendTorque();
        }
        
        if (counter % 20 == 7)
        {
            sendSteeringWheel();
            sendSteeringWheelDSC();
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
            sendOilLevel();
        }

        if (counter % 100 == 0)
        {
            sendTime();
        }

        counter++;
        previous = current;
    }
}
