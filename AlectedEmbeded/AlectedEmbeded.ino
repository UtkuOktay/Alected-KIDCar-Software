
void setup(){
  motor_driver_setup();
  display_setup();
  telemetry_setup();
}

void loop() {
  motor_driver_loop();
  display_loop();
  telemetry_loop();
}
