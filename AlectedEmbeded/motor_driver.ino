#define throttle_pin A0

#define A_HI 7
#define A_LO 8
#define B_HI 9
#define B_LO 10
#define C_HI 11
#define C_LO 12

#define hall_A 18
#define hall_B 19
#define hall_C 20

int hall_A_state = 0;
int hall_B_state = 0;
int hall_C_state = 0;

int hall_overall_state = 0;

int throttle = 0;
int pwm = 0;

int direction = 1; //1: Forward, 0: Reverse

const byte sequence[6][6] = {
  {0, 0, 1, 0, 0, 1},
  {1, 0, 0, 1, 0, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0}
};

void motor_driver_setup() {
  attachInterrupt(digitalPinToInterrupt(hall_A), changePhase, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hall_B), changePhase, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hall_C), changePhase, CHANGE);
  pinMode(A_HI, OUTPUT);
  pinMode(A_LO, OUTPUT);
  pinMode(B_HI, OUTPUT);
  pinMode(B_LO, OUTPUT);
  pinMode(C_HI, OUTPUT);
  pinMode(C_LO, OUTPUT);

  pinMode(hall_A, INPUT_PULLUP);
  pinMode(hall_B, INPUT_PULLUP);
  pinMode(hall_C, INPUT_PULLUP);

  pwm = 200;

  changePhase();
}

//Sets all the pins to low.
void resetPins() {
  digitalWrite(A_LO, LOW);
  digitalWrite(B_LO, LOW);
  digitalWrite(C_LO, LOW);
  digitalWrite(A_HI, LOW);
  digitalWrite(B_HI, LOW);
  digitalWrite(C_HI, LOW);
}

void setPins() {
  //3 of hall sensor values cannot be all 0s or 1s at the same time. Such values indicate a problem. Immidiately turn off the motor!!!
  if (hall_overall_state >= 0 && hall_overall_state < 6) {
    if (direction) { //FORWARD
      analogWrite(A_HI, sequence[hall_overall_state][0] * pwm);
      digitalWrite(A_LO, sequence[hall_overall_state][1]);
      analogWrite(B_HI, sequence[hall_overall_state][2] * pwm);
      digitalWrite(B_LO, sequence[hall_overall_state][3]);
      analogWrite(C_HI, sequence[hall_overall_state][4] * pwm);
      digitalWrite(C_LO, sequence[hall_overall_state][5]);
    }
    else { //REVERSE (B and C are interchanged)
      analogWrite(A_HI, sequence[hall_overall_state][0] * pwm);
      digitalWrite(A_LO, sequence[hall_overall_state][1]);
      analogWrite(C_HI, sequence[hall_overall_state][2] * pwm);
      digitalWrite(C_LO, sequence[hall_overall_state][3]);
      analogWrite(B_HI, sequence[hall_overall_state][4] * pwm);
      digitalWrite(B_LO, sequence[hall_overall_state][5]);
    }
  }
  else {
    resetPins();
    Serial.println("Incorrect Hall Sensor Values");
  }
}


void changePhase() {
  resetPins();
  hall_A_state = digitalRead(hall_A);
  hall_B_state = digitalRead(hall_B);
  hall_C_state = digitalRead(hall_C);
  hall_overall_state = hall_A_state * 4 + hall_B_state * 2 + hall_C_state - 1;
  setPins();
}

void readThrottle() {
  throttle = map(digitalRead(throttle_pin), 175, 850, 0, 100);
  
  pwm = map(throttle, 0, 100, 0, 240);
  
  if (pwm < 10)
    pwm = 0;
  
  if (pwm > 240)
    pwm = 240;
}

void motor_driver_loop() {
  //readThrottle();
  
  if (pwm > 10)
    setPins();
  else
    resetPins();
}
