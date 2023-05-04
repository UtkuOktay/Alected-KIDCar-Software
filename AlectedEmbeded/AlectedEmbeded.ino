
void setup(){
  motor_driver_setup();
  sensors_setup();
  display_setup();
  telemetry_setup();
}

void loop() {
  //motor_driver_loop();
  sensors_loop();
  //display_loop();
  //telemetry_loop();
}
