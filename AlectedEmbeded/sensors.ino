
int sensor_throttle;
int sensor_motor_temp;
int sensor_driver_temp;
int sensor_voltage;
float battery_percentage;
float V = 5;

#define throttle_pin A0
#define motor_temp_pin A1
#define driver_temp_pin A2
#define voltage_pin A3

void sensors_setup(){
  
  pinMode(throttle_pin, INPUT);
  pinMode(motor_temp_pin, INPUT);
  pinMode(driver_temp_pin, INPUT);
  pinMode(voltage_pin, INPUT);

  Serial.begin(9600);
}

float interprete_battery_percentage(float voltage){
  float charge_left = -3142.3*pow(voltage,6) + 54836*pow(voltage,5) - 389293*pow(voltage,4) + 1*pow(10,6)*pow(voltage,2) + 3*pow(10,6) * voltage - 1E+06;
  charge_left = 3325 - charge_left;
  return (charge_left / 3325) * 100; 
}

float interperate_temperature(int sensor_input){
  float VCC = 5;
  float R = 10000;
  float B = 3977;
  float RT0 = 10000;
  float T0 = 25 + 273.15;

  float VRT = (5.00 / 1023.00) * sensor_input;    //Conversion to voltage
  float VR = VCC - VRT;
  float RT = VRT / (VR / R);                      //Resistance of RT
  float ln = log(RT / RT0);
  float TX = (1 / ((ln / B) + (1 / T0)));         //Temperature from thermistor
  return TX - 273.15;    
}

void sensors_loop(){
  sensor_throttle = map(analogRead(throttle_pin), 175, 850, 0, 100);
  sensor_motor_temp = analogRead(motor_temp_pin);
  sensor_driver_temp = analogRead(driver_temp_pin);
  sensor_voltage = analogRead(voltage_pin);
  interprete_battery_percentage(V);

  //Serial.println("senrsor: " + String(sensor_throttle));
  //Serial.println("motor_temp_raw: " + String(sensor_motor_temp));
  //Serial.println("driver_temp_raw: " + String(sensor_driver_temp));

  Serial.println("motor_temp: " + String(interperate_temperature(sensor_motor_temp)));
  //Serial.println("driver_temp: " + String(interperate_temperature(sensor_driver_temp)));

}
