
extern float velocity;
extern float values[];

char termination_character = '\n';

void telemetry_setup(){
	Serial1.begin(9600);

}

void telemetry_loop(){
  Serial1.print(velocity)
  for (int i = 0; i < 6; i++){
    Serial1.print(values[i]);
  }
  Serial1.print(termination_character);
}