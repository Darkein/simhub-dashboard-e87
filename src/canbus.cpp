#include <canbus.h>
#include <globals.h>

const uint32_t _10ms = 10000;
const uint32_t _50ms = 50000;
const uint32_t _200ms = 200000;
const uint32_t _500ms = 500000;
const uint32_t _1000ms = 1000000;
const uint32_t _2000ms = 2000000;

//2.2s = 12s
//2s = 4mn

void sendCanBus()
{
    uint32_t now = micros();

    static uint32_t last10ms = 0;
    static uint32_t last50ms = 0;
    static uint32_t last200ms = 0;
    static uint32_t last500ms = 0;
    static uint32_t last1000ms = 0;
    static uint32_t last2000ms = 0;

    // Toutes les 10ms
    if (now - last10ms >= _10ms)
    {

        sendIgnition();
        sendGearStatus();
        sendSteeringWheel();
        sendCruiseControl();
        sendVehicleDynamics();
        sendIndicators();

        last10ms += _10ms;
        now = micros();
    }

    // Toutes les 50ms
    if (now - last50ms >= _50ms)
    {
        sendSpeed();
        sendRpm();
        sendEngineTempAndFuelInjection();
        sendErrorLights();
        sendTorque();

        last50ms += _50ms;
        now = micros();
    }

    if (now - last200ms >= _200ms)
    {

        sendAbs();
        sendLightning();
        sendAirbag();
        sendFuel();
        sendHandbrake();
        sendSeatbelt();

        last200ms += _200ms;
        now = micros();
    }

    if (now - last500ms >= _500ms)
    {
        sendOilLevel();
        last500ms += _500ms;
        now = micros();
    }

    if (now - last1000ms >= _1000ms)
    {
        sendTime();
        last1000ms += _1000ms;
        now = micros();
    }

    if (now - last2000ms >= _2000ms)
    {
        sendSteeringWheelEPS();
        last2000ms += _2000ms;
        now = micros();
    }
}
