#include <globals.h>
#include <serial.h>

void readSerial()
{
    while (Serial.available())
    {
        if (Serial.readStringUntil(';') != "SH")
        {
            continue;
        }

        bool ignition = Serial.readStringUntil(';').toInt();
        bool engine_running = Serial.readStringUntil(';').toInt();
        bool check_engine = Serial.readStringUntil(';').toInt();

        bool lights_side = Serial.readStringUntil(';').toInt();
        bool lights_dip = Serial.readStringUntil(';').toInt();
        bool lights_main = Serial.readStringUntil(';').toInt();
        bool lights_front_fog = Serial.readStringUntil(';').toInt();
        bool lights_rear_fog = Serial.readStringUntil(';').toInt();
        uint8_t lights_indicators = Serial.readStringUntil(';').toInt();

        uint16_t rpm = Serial.readStringUntil(';').toInt();
        uint8_t throttle = Serial.readStringUntil(';').toInt();
        uint16_t torque = Serial.readStringUntil(';').toInt();
        uint16_t speed = Serial.readStringUntil(';').toInt();
        uint8_t fuel = Serial.readStringUntil(';').toInt();

        uint8_t engine_temperature = Serial.readStringUntil(';').toInt();

        bool handbrake = Serial.readStringUntil(';').toInt();
        bool abs = Serial.readStringUntil(';').toInt();
        bool tc = Serial.readStringUntil(';').toInt();
        bool airbag = Serial.readStringUntil(';').toInt();
        bool seatbelt = Serial.readStringUntil(';').toInt();
        bool door_open = Serial.readStringUntil(';').toInt();

        uint8_t cruise_speed = Serial.readStringUntil(';').toInt();
        bool cruise_enabled = Serial.readStringUntil(';').toInt();

        uint8_t fuel_injection = Serial.readStringUntil(';').toInt();
        uint8_t water_temp = Serial.readStringUntil(';').toInt();
        bool low_oil_pressure = Serial.readStringUntil(';').toInt();
        
        uint8_t time_hour = Serial.readStringUntil(';').toInt();
        uint8_t time_minute = Serial.readStringUntil(';').toInt();
        uint8_t time_second = Serial.readStringUntil(';').toInt();
        uint8_t time_day = Serial.readStringUntil(';').toInt();
        uint8_t time_month = Serial.readStringUntil(';').toInt();
        uint16_t time_year = Serial.readStringUntil(';').toInt();

        String noop = Serial.readStringUntil('\n');

        g_ignition = ignition;
        g_engine_running = engine_running;
        g_check_engine = check_engine;

        g_lights_side = lights_side;
        g_lights_dip = lights_dip;
        g_lights_main = lights_main;
        g_lights_front_fog = lights_front_fog;
        g_lights_rear_fog = lights_rear_fog;
        g_lights_indicators = lights_indicators;

        g_rpm = rpm;
        g_throttle = throttle;
        g_max_torque = torque;
        g_speed = speed;
        g_fuel = fuel;

        g_engine_temperature = engine_temperature;
        g_cruise_speed = cruise_speed;
        g_cruise_enabled = cruise_enabled;

        g_fuel_injection = fuel_injection;
        g_water_temp = water_temp;
        g_low_oil_pressure = low_oil_pressure;

        g_handbrake = handbrake;
        g_abs = abs;
        g_tc = tc;
        g_airbag = airbag;
        g_seatbelt = seatbelt;
        g_door_open = door_open;

        g_time_hour = time_hour;
        g_time_minute = time_minute;
        g_time_second = time_second;
        g_time_day = time_day;
        g_time_month = time_month;
        g_time_year = time_year;
    }
}