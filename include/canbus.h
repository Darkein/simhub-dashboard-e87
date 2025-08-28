#include <Arduino.h>

void sendCanBus();

void sendIgnition();
void sendLightning();
void sendRpm();
void sendSpeed();
void sendTorque();
void sendVehicleDynamics();
void sendFuel();
void sendEngineTemperature();
void sendOilLevel();
void sendSteeringWheel();
void sendSteeringWheelFast();
void sendSteeringWheelDSC();
void sendSteeringWheelControl(int button);
void sendErrorLights();
void sendCruiseControl();
void sendDmeStatus();
void sendHandbrake();
void sendAbs();
void sendAirbag();
void sendSeatbelt();
void sendTime();
void sendIndicators();
void sendGearStatus();