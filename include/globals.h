#include <mcp_can.h>

extern MCP_CAN CAN;

extern bool g_ignition;
extern bool g_engine_running;
extern bool g_check_engine;

extern bool g_lights_side;
extern bool g_lights_dip;
extern bool g_lights_main;
extern bool g_lights_front_fog;
extern bool g_lights_rear_fog;
extern uint8_t g_lights_indicators;

extern uint16_t g_rpm;
extern uint8_t g_throttle;
extern uint16_t g_speed_mph;
extern uint16_t g_speed_kph;
extern uint8_t g_fuel;
extern uint16_t g_max_torque;

extern uint16_t g_cruise_speed;
extern bool g_cruise_enabled;

extern float g_l_100km;
extern uint8_t g_water_temp;

extern uint8_t g_oil_temp;

extern bool g_handbrake;
extern bool g_abs;
extern bool g_tc;
extern bool g_airbag;
extern bool g_seatbelt;
extern bool g_door_open;
extern bool g_low_oil_pressure;

extern uint8_t g_time_hour;
extern uint8_t g_time_minute;
extern uint8_t g_time_second;
extern uint8_t g_time_day;
extern uint8_t g_time_month;
extern uint16_t g_time_year;

enum GearState {
  GearState_Manual_1 = 1,
  GearState_Manual_2 = 2,
  GearState_Manual_3 = 3,
  GearState_Manual_4 = 4,
  GearState_Manual_5 = 5,
  GearState_Manual_6 = 6,
  GearState_Manual_7 = 7,
  GearState_Manual_8 = 8,
  GearState_Manual_9 = 9,
  GearState_Manual_10 = 10,
  GearState_Auto_P = 11,
  GearState_Auto_R = 12,
  GearState_Auto_N = 13,
  GearState_Auto_D = 14,
  GearState_Auto_S = 15
};

extern enum GearState g_gear;