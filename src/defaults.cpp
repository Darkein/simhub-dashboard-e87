#include <globals.h>

bool g_ignition = false;
bool g_engine_running = false;
bool g_check_engine = false;

bool g_lights_side = false;
bool g_lights_dip = false;
bool g_lights_main = false;
bool g_lights_front_fog = false;
bool g_lights_rear_fog = false;
uint8_t g_lights_indicators = 0;

uint16_t g_rpm = 0;
uint16_t g_speed_mph = 0;
uint16_t g_speed_kph = 0;
uint8_t g_fuel = 0;
uint8_t g_throttle = 0;
uint16_t g_max_torque = 0;

float g_l_100km = 0;
uint8_t g_water_temp = 0;

bool g_cruise_enabled = true;
uint16_t g_cruise_speed = 0;

uint8_t g_oil_temp = 0;

bool g_handbrake = false;
bool g_abs = false;
bool g_tc = false;
bool g_airbag = false;
bool g_seatbelt = false;
bool g_door_open = false;
bool g_low_oil_pressure = false;
bool g_car_ahead = false;
bool g_low_pressure_front_left = false;
bool g_low_pressure_front_right = false;
bool g_low_pressure_rear_left = false;
bool g_low_pressure_rear_right = false;


enum GearState g_gear = GearState_Auto_P;

uint8_t g_time_hour = 0;
uint8_t g_time_minute = 0;
uint8_t g_time_second = 0;
uint8_t g_time_day = 0;
uint8_t g_time_month = 0;
uint16_t g_time_year = 0;