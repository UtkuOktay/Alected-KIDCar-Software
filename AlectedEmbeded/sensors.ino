
int sensor_throttle;
int sensor_temp0;
int sensor_temp1;

#define throttle_pin A0
#define temp_pin0 A1
#define temp_pin1 A2

void sensors_setup(){
  pinMode(temp_pin0, INPUT);
  pinMode(temp_pin1, INPUT);

  Serial.begin(9600);
}

void sensors_loop(){
  sensor_throttle = map(analogRead(throttle_pin), 175, 850, 0, 100);   // analogRead olması gerekmiyor mu Utku'ya sor
  sensor_temp0 = analogRead(temp_pin0);
  sensor_temp1 = analogRead(temp_pin1);
  Serial.println("senrsor: " + sensor_throttle);
  Serial.println("temp0: " + sensor_temp0);
  Serial.println("temp1: " + sensor_temp1);
}