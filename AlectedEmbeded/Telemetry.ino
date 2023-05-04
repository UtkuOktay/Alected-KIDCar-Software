
extern float velocity;
extern float chart_values[];

char termination_character = '\n';

void telemetry_setup(){
	Serial1.begin(9600);

}

// data format; velocity(float) motor_temperature(float) driver_temperature(float) current(float) voltage(float) battary_persentage(float) 6th_parameter(float) termination_character(1byte) 

void telemetry_loop(){
  Serial1.print(velocity);
  for (int i = 0; i < 6; i++){
    Serial1.print(chart_values[i]);
  }
  Serial1.print(termination_character);
}