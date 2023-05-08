#include "debug.h"

void setup(){
  motor_driver_setup();
  sensors_setup();
  display_setup();
  telemetry_setup();
}

unsigned int motor_compute_priority = 50;
unsigned int sensor_compute_priority = 5;
unsigned int display_compute_priority = 1;
unsigned int telemetry_compute_priority = 5;

unsigned int _motor_compute_iterator = 0;
unsigned int _sensor_compute_iterator = 0;
unsigned int _display_compute_iterator = 0;
unsigned int _telemetry_compute_iterator = 0;

void loop() {
  if(_motor_compute_iterator > 0){
    motor_driver_loop();   // 0.05ms
    _motor_compute_iterator--;
  }
  if(_sensor_compute_iterator > 0){
    sensors_loop();   // 2.34 ms
    _sensor_compute_iterator--;
  }
  if(_display_compute_iterator > 0){
    display_loop(); // 135ms
    _display_compute_iterator--;
  }
  if(_telemetry_compute_iterator > 0){
    telemetry_loop(); // 4.90 ms;
    _telemetry_compute_iterator--;
  }
  if (!_motor_compute_iterator && !_sensor_compute_iterator && !_display_compute_iterator && !_telemetry_compute_iterator){
    _motor_compute_iterator = motor_compute_priority;
    _sensor_compute_iterator = sensor_compute_priority;
    _display_compute_iterator = display_compute_priority;
    _telemetry_compute_iterator = telemetry_compute_priority;
  }

}
