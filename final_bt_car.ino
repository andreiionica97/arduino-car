#define lMotors 9 //left motors
#define pin1 4
#define pin2 5
#define rMotors 10 //right motors
#define pin3 6
#define pin4 7

int xAxis, yAxis;
int  x = 0;
int  y = 0;

int lMotorSpeed1 = 0;
int lMotorSpeed2 = 0;

void setup() {
  pinMode(lMotors, OUTPUT);
  pinMode(rMotors, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //default value - no movement
  xAxis = 510;
  yAxis = 510;

  //read data from app
  while (Serial.available() >= 2) {
    x = Serial.read();
    //Serial.print("x = ");
    //Serial.print(x);
    delay(10);
    y = Serial.read();
    //Serial.print("y = ");
    //Serial.print(y);
    //Serial.print("\n");
  }
  delay(10);
  
  //check if the values recived are ok
  if (x > 60 & x < 255) {
    xAxis = map(x, 220, 60, 1023, 0); //maps x and y values to 0 - 1023 range
  }
  if (y > 60 & y < 255) {
    yAxis = map(y, 220, 60, 0, 1023);
  }
  //backward movement
  if (yAxis < 470) {
    //motor a
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    //motor b
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
    //transforms y in 0 - 255 range for pwm signal
    lMotorSpeed1 = map(yAxis, 470, 0, 0, 255);
    lMotorSpeed2 = map(yAxis, 470, 0, 0, 255);
  }
  //forward movement
  else if (yAxis > 550) {
    //motor a
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    //motor b
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
    //transforms y in 0 - 255 range for pwm signal
    lMotorSpeed1 = map(yAxis, 550, 1023, 0, 255);
    lMotorSpeed2 = map(yAxis, 550, 1023, 0, 255);
  }
  //initial position - no movement
  else {
    lMotorSpeed1 = 0;
    lMotorSpeed2 = 0;
  }

  //left movement
  if (xAxis < 470) {
    //transforms x in 0 - 255 range for pwm signal
    int xMapped = map(xAxis, 470, 0, 0, 255);
    lMotorSpeed1 = lMotorSpeed1 - xMapped;
    lMotorSpeed2 = lMotorSpeed2 + xMapped;
    //confine range from 0 - 255
    if (lMotorSpeed1 < 0) {
      lMotorSpeed1 = 0;
    }
    if (lMotorSpeed2 > 255) {
      lMotorSpeed2 = 255;
    }
  }
  //right movement
  if (xAxis > 550) {
    //transforms x in 0 - 255 range for pwm signal
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    lMotorSpeed1 = lMotorSpeed1 + xMapped;
    lMotorSpeed2 = lMotorSpeed2 - xMapped;
    //confine range from 0 - 255
    if (lMotorSpeed1 > 255) {
      lMotorSpeed1 = 255;
    }
    if (lMotorSpeed2 < 0) {
      lMotorSpeed2 = 0;
    }
  }
  //stop movement at low speed
  if (lMotorSpeed1 < 70) {
    lMotorSpeed1 = 0;
  }
  if (lMotorSpeed2 < 70) {
    lMotorSpeed2 = 0;
  }
  analogWrite(lMotors, lMotorSpeed1); //pwm signal to left motors
  analogWrite(rMotors, lMotorSpeed2); //pwm signal to right motors
}
