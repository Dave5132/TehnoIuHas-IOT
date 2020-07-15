//Stepper decrare
#include <Stepper.h>
const int stepsPerRevolution = 2048;
int x = 1, a = 0, b = 0, y = 0, active = 0, something = 0;
char comands, number;

Stepper myStepper1 = Stepper(stepsPerRevolution, 0, 1, 2,3);
Stepper myStepper2 = Stepper(stepsPerRevolution, 4, 5, 6, 7);
//Laser and resistor
#define laser_out 8
#define laser_in 9
#define resistor_out 10
#define resistor_in 11
//Button
#define button 12
//Ultrasonic
#define echo_r 13
#define trig_r 14
#define echo_l 15
#define trig_l 16
float ultra_r, ultra_l;
//Led
#define RED 17
#define BLUE 18
#define GREEN 19
//Remote
#include <IRremote.h>
#define button_1 0x490
#define button_2 0x40
int RECV_PIN = 20;
IRrecv irrecv(RECV_PIN);
decode_results results;
//Buzzer
const int buzzer = 21;
//4 pe 7
#define pinA  22
#define pinB  23
#define pinC  24
#define pinD  25
#define pinE  26
#define pinF  27
#define pinG  28
#define D1  29
#define D2 30
#define D3 31
#define D4  32
//Sensor helpers
boolean freeze = false;
unsigned long lastMillis1;
unsigned long lastMillis2;

void setup() {
  Serial.begin(9600);
  myStepper1.setSpeed(5);
  myStepper2.setSpeed(5);
  pinMode(button, INPUT_PULLUP);
  pinMode(echo_r, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_l, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(buzzer, OUTPUT);
  irrecv.enableIRIn();
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  lastMillis1 = millis();
  lastMillis2 = millis();
  lastMillis2 = -100000;
  lastMillis1 = -100000;
}

void loop() {
  Serial.println("Este");
  int laser_read_in = analogRead(resistor_in);
  int laser_read_out = analogRead(resistor_out);
  //Read ultrasonic
  //  ultra_r = Ultrasonic(trig_r, echo_r);
  //  ultra_l = Ultrasonic(trig_l, echo_l);
  //Read from wed
  comands = Serial.read();
  switch (comands) {
    case '0':
      if (x % 2 == 0) {
        x += 1;
      }
      lastMillis1 = millis();
      active = 2;
      Serial.println("Open");
      break;
    case'1':
      if (something == 1) {
        if (x % 2 == 0) {
          x += 1;
        }
        lastMillis2 = millis();
        active = 1;
        Serial.println("Close");
        break;
      }
  }
  //Red from iRemote
  if (irrecv.decode(&results))
  {
    switch (results.value) {
      case button_1:
        if (x % 2 == 0) {
          x += 1;
        }
        lastMillis1 = millis();
        active = 2;
        Serial.println("Open");
        break;
      case button_2:
        if (x % 2 == 0) {
          x += 1;
        }
        if (something == 1) {
          lastMillis2 = millis();
          active = 1;
          Serial.println("Close");
          break;
        }
    }
    irrecv.resume();
  }
  //Button read
  if (button == 0) {
    if (not freeze)
    {
      freeze = true;
      x += 1;
      delay(500);
      freeze = false;
    }
  }
  if (x % 2 == 0) {
    if (active == 1) {
      lastMillis1 = millis();
      active = 2;
      Serial.println("Open");
    }
    else {
      lastMillis2 = millis();
      active = 1;
      Serial.println("Close");
    }
  }

  //Open the garage
  if (millis() - lastMillis1 <= 10000  ) {
    myStepper1.step(-stepsPerRevolution);
    myStepper2.step(stepsPerRevolution);
    RGB_LED(255, 255, 255);
  }
  //Close de door
  if (millis() - lastMillis2 <= 10000  ) {
    myStepper1.step(stepsPerRevolution);
    myStepper2.step(-stepsPerRevolution);
    RGB_LED(255, 255, 255);
  }

  //Start all sensor for parking
  if (active == 2) {
    digitalWrite(laser_out, HIGH);
    digitalWrite(laser_in, HIGH);
    if (laser_read_out < 40) {
      something = 2;
    }
    else
    {
      something = 1;
    }
    if (laser_read_in < 40) {
      RGB_LED(255, 0, 0);
    }
    else if (ultra_r < 10 || ultra_l < 10) {
      RGB_LED(255, 0, 0);
    }
    else {
      RGB_LED(255, 255, 255);
    }
        if (ultra_r < ultra_l) {
          number = ultra_r / 10;
        }
        else {
          number = ultra_l / 10;
        }
  }
  else {
    digitalWrite(laser_out, LOW);
    digitalWrite(laser_in, LOW);
    number = '0';
  }

  //Print all numbers for panel
    switch (number) {
      case '0':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        break;
      case'1':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, LOW);
        break;
      case'2':
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, HIGH);
        digitalWrite(pinG, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, HIGH);
        break;
      case'3':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, HIGH);
        break;
      case'4':
        digitalWrite(pinA, HIGH);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        break;
      case'5':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        break;
      case'6':
  
        //6
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        break;
      case'7':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, HIGH);
        digitalWrite(pinG, HIGH);
        break;
      case'8':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, LOW);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        break;
      case'9':
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, LOW);
        digitalWrite(pinC, LOW);
        digitalWrite(pinD, HIGH);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, LOW);
        break;
    }

}
float Ultrasonic(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
void RGB_LED(int value, int value2, int value3) {
  analogWrite(RED, value);
  analogWrite(BLUE, value2);
  analogWrite(GREEN, value3);
}
