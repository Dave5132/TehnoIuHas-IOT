//RGB_LED//
#define LED_RED 0
#define LED_GREEN 1
#define LED_BLUE 2
#define LED1_RED 3
#define LED1_GREEN 4
#define LED1_BLUE 5
#define LED2_RED 6
#define LED2_GREEN 7
#define LED2_BLUE 8
#define LED3_RED 9
#define LED3_GREEN 10
#define LED3_BLUE 11
#define LED4_RED 12
#define LED4_GREEN 13
#define LED4_BLUE 14
#define LED5_RED 15
#define LED5_GREEN 16
#define LED5_BLUE 17
#define LED6_RED 18
#define LED6_GREEN 19
#define LED6_BLUE 20
#define LED7_RED 21
#define LED7_GREEN 22
#define LED7_BLUE 23
#define LED8_RED 24
#define LED8_GREEN 25
#define LED8_BLUE 26
#define LED9_RED 27
#define LED9_GREEN 28
#define LED9_BLUE 29
#define LED10_RED 30
#define LED10_GREEN 31
#define LED10_BLUE 32
#define LED11_RED 33
#define LED11_GREEN 34
#define LED11_BLUE 35
#define LED12_RED 36
#define LED12_GREEN 37
#define LED12_BLUE 38
#define LED13_RED 39
#define LED13_GREEN 40
#define LED13_BLUE 41
//led
#define LED 42
//JoyStick//
#define SW 43
int VRx = A0;
int VRy = A1;
const int redX = 512;
const int redY = 1023;
const int greenX = 1023;
const int greenY = 0;
const int blueX = 0;
const int blueY = 0;
boolean freeze = false;
int x, xAxis, yAxis, SW_state, brightRed, brightGreen, brightBlue, distanceRed, distanceGreen, distanceBlue;
//pontetiomentru
int potPin = 2;
int val = 0;
//PIR MOTION SENSOR//
int led_1 = 1, led_2 = 1, led_3 = 1, led_4 = 1, led_5 = 1, led_6 = 1, led_7 = 1, led_8 = 1;
#define PIR_OUTF A3
#define PIR_IN A4
#define PIR_OUTB A5
//LDR_PIN//
#define LDR_IN A6
#define LDR_OUT A7
//MICROFONE//
#define Micro 44// millis
//Millis for senzor
unsigned long lastMillis1;
unsigned long lastMillis2;
unsigned long lastMillis3;
unsigned long lastMillis4;
int auto_1;
//Read wed
char reader;

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);
  pinMode(LED2_RED, OUTPUT);
  pinMode(LED2_GREEN, OUTPUT);
  pinMode(LED2_BLUE, OUTPUT);
  pinMode(LED3_RED, OUTPUT);
  pinMode(LED3_GREEN, OUTPUT);
  pinMode(LED3_BLUE, OUTPUT);
  pinMode(LED4_RED, OUTPUT);
  pinMode(LED4_GREEN, OUTPUT);
  pinMode(LED4_BLUE, OUTPUT);
  pinMode(LED5_RED, OUTPUT);
  pinMode(LED5_GREEN, OUTPUT);
  pinMode(LED5_BLUE, OUTPUT);
  pinMode(LED6_RED, OUTPUT);
  pinMode(LED6_GREEN, OUTPUT);
  pinMode(LED6_BLUE, OUTPUT);
  pinMode(LED7_RED, OUTPUT);
  pinMode(LED7_GREEN, OUTPUT);
  pinMode(LED7_BLUE, OUTPUT);
  pinMode(LED8_RED, OUTPUT);
  pinMode(LED8_GREEN, OUTPUT);
  pinMode(LED8_BLUE, OUTPUT);
  pinMode(LED9_RED, OUTPUT);
  pinMode(LED9_GREEN, OUTPUT);
  pinMode(LED9_BLUE, OUTPUT);
  pinMode(LED10_RED, OUTPUT);
  pinMode(LED10_GREEN, OUTPUT);
  pinMode(LED10_BLUE, OUTPUT);
  pinMode(LED11_RED, OUTPUT);
  pinMode(LED11_GREEN, OUTPUT);
  pinMode(LED11_BLUE, OUTPUT);
  pinMode(LED12_RED, OUTPUT);
  pinMode(LED12_GREEN, OUTPUT);
  pinMode(LED12_BLUE, OUTPUT);
  pinMode(LED13_RED, OUTPUT);
  pinMode(LED13_GREEN, OUTPUT);
  pinMode(LED13_BLUE, OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(PIR_IN, INPUT);
  pinMode(PIR_OUTF, INPUT);
  pinMode(PIR_OUTB, INPUT);
  pinMode(LDR_IN, INPUT);
  pinMode(LDR_OUT, INPUT);
  pinMode(Micro, INPUT);
  pinMode(LED, OUTPUT);
  lastMillis1 = millis();
  lastMillis2 = millis();
  lastMillis3 = millis();
  lastMillis4 = millis();
}

void loop() {
  Serial.println("est");
  //Joystick
  xAxis = analogRead(VRx);
  yAxis = analogRead(VRy);
  SW_state = digitalRead(SW);
  xAxis = map(xAxis, 0, 1023, 0, 1023);
  yAxis = map(yAxis, 0, 1023, 1023, 0);
  distanceRed = sqrt(pow(abs(redX - xAxis), 2) +  pow(abs(redY - yAxis), 2));
  distanceGreen = sqrt(pow(abs(greenX - xAxis), 2) +  pow(abs(greenY - yAxis), 2));
  distanceBlue = sqrt(pow(abs(blueX - xAxis), 2) +  pow(abs(blueY - yAxis), 2));
  //Read from phone
  reader = Serial.read();
  switch (reader) {
    case'0':
      if (led_1 % 2 == 0) {
        led_1 += 1;
      }
      if (led_2 % 2 == 0) {
        led_2 += 1;
      }
      if (led_3 % 2 == 0) {
        led_3 += 1;
      }
      if (led_4 % 2 == 0) {
        led_4 += 1;
      }
      if (led_5 % 2 == 0) {
        led_5 += 1;
      }
      if (led_6 % 2 == 0) {
        led_6 += 1;
      }
      if (led_7 % 2 == 0) {
        led_7 += 1;
      }
      if (led_8 % 2 == 0) {
        led_8 += 1;
      }
      break;
    case '1':
      led_1 += 1;
      break;
    case '2':
      led_2 += 1;
      break;
    case '3':
      led_3 += 1;
      break;
    case '4':
      led_4 += 1;
      break;
    case '5':
      led_5 += 1;
      break;
    case '6':
      led_6 += 1;
      break;
    case '7':
      led_7 += 1;
      break;
    case'8':
      led_8 += 1;
      break;
    case'9':
      auto_1 += 1;
      break;
  }
  //off all led

  //Led ON//OFF
  if (led_1 % 2 == 0) {
    RGB_COLOR_ON(LED7_RED, LED7_GREEN, LED7_BLUE);
    Serial.println("Led On");
  }
  else {
    RGB_COLOR_OFF(LED7_RED, LED7_GREEN, LED7_BLUE);
    Serial.println("Led OFf");
  }
  if (led_2 % 2 == 0) {
    RGB_COLOR_ON(LED8_RED, LED8_GREEN, LED8_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED8_RED, LED8_GREEN, LED8_BLUE);
  }
  if (led_3 % 2 == 0) {
    RGB_COLOR_ON(LED9_RED, LED9_GREEN, LED9_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED9_RED, LED9_GREEN, LED9_BLUE);
  }
  if (led_4 % 2 == 0) {
    RGB_COLOR_ON(LED10_RED, LED10_GREEN, LED10_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED10_RED, LED10_GREEN, LED10_BLUE);
  }
  if (led_5 % 2 == 0) {
    RGB_COLOR_ON(LED11_RED, LED11_GREEN, LED11_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED11_RED, LED11_GREEN, LED11_BLUE);
  }
  if (led_6 % 2 == 0) {
    RGB_COLOR_ON(LED12_RED, LED12_GREEN, LED12_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED12_RED, LED12_GREEN, LED12_BLUE);
  }
  if (led_7 % 2 == 0) {
    RGB_COLOR_ON(LED13_RED, LED13_GREEN, LED13_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED13_RED, LED13_GREEN, LED13_BLUE);
  }
  if (led_8 % 2 == 0) {
    RGB_COLOR_ON(LED6_RED, LED6_GREEN, LED6_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED6_RED, LED6_GREEN, LED6_BLUE);
  }

  //Pontetiometrul
  val = analogRead(potPin);
  RGB_PONTETIOMETER(val, val, val);
  //Senzorul de miscare
  //////////////////////////////////////////////////////////
  if (Get_PIR_F() == 1 && Get_LT_OUT() < 30) {
    lastMillis2 = millis();
  }

  if (millis() - lastMillis2 <= 7000) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  /////////////////////////////////////////////////////////
  if (Get_PIR_B() == 1 && Get_LT_OUT() < 30) {
    lastMillis3 = millis();
  }

  if (millis() - lastMillis3 <= 7000) {
    RGB_COLOR_ON(LED4_RED, LED4_GREEN, LED4_BLUE);
    RGB_COLOR_ON(LED5_RED, LED5_GREEN, LED5_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED4_RED, LED4_GREEN, LED4_BLUE);
    RGB_COLOR_OFF(LED5_RED, LED5_GREEN, LED5_BLUE);
  }
  ////////////////////////////////////////////////////
  if (auto_1 % 2 == 0) {
    if (SW_state == 0) {
      if (not freeze)
      {

        freeze = true;
        x += 1;
        delay(500);
        freeze = false;
      }
    }
    else {
      x = x;
    }
  }
  else {
    if (Get_PIR_IN() == 1 && Get_LT_IN() > 30) {
      lastMillis4 = millis();
    }
  }
  if (millis() - lastMillis4 <= 7000) {
    RGB_COLOR(255, 255, 255);
  }
  else {
    RGB_COLOR(0, 0, 0);
  }


  //Microfone
  if (Micro == 1) {
    lastMillis1 = millis();
  }
  if (millis() - lastMillis1 <= 7000) {
    RGB_COLOR_ON(LED3_RED, LED3_GREEN, LED3_BLUE);
  }
  else {
    RGB_COLOR_OFF(LED3_RED, LED3_GREEN, LED3_BLUE);
  }

  //Joystick//

  if (x % 2 == 0) {
    RGB_COLOR(brightRed, brightGreen, brightBlue);
  }
  else {
    if (xAxis < 5 && yAxis < 5) {
      brightRed = 0;
      brightGreen = 0;
      brightBlue = 0;
      RGB_COLOR(brightRed, brightGreen, brightBlue);
    }
    else {
      brightRed = 255 - constrain(map(distanceRed, 0, 1023, 0, 255), 0, 255);
      brightGreen = 255 - constrain(map(distanceGreen, 0, 1023, 0, 255), 0, 255);
      brightBlue = 255 - constrain(map(distanceBlue, 0, 1023, 0, 255), 0, 255);
      RGB_COLOR(brightRed, brightGreen, brightBlue);
    }
  }
}
void RGB_COLOR (int red_value, int green_value, int blue_value) {
  analogWrite(LED_RED, red_value);
  analogWrite(LED_GREEN, green_value);
  analogWrite(LED_BLUE, blue_value);
  analogWrite(LED1_RED, red_value);
  analogWrite(LED1_GREEN, green_value);
  analogWrite(LED1_BLUE, blue_value);
  analogWrite(LED2_RED, red_value);
  analogWrite(LED2_GREEN, green_value);
  analogWrite(LED2_BLUE, blue_value);
}
void RGB_PONTETIOMETER (int red_value, int green_value, int blue_value) {
  analogWrite(LED7_RED, red_value);
  analogWrite(LED7_GREEN, green_value);
  analogWrite(LED7_BLUE, blue_value);
}
void RGB_COLOR_ON(int RED_PIN, int GREEN_PIN, int BLUE_PIN) {
  analogWrite(GREEN_PIN, 255);
  analogWrite(RED_PIN, 255);
  analogWrite(BLUE_PIN, 255);
}
void RGB_COLOR_OFF(int RED_PIN, int GREEN_PIN, int BLUE_PIN) {
  analogWrite(GREEN_PIN, 0);
  analogWrite(RED_PIN, 0);
  analogWrite(BLUE_PIN, 0);
}
int Get_PIR_F() {
  int sensorState = digitalRead(PIR_OUTF);
  return sensorState;
}
int Get_PIR_B() {
  int sensorState = digitalRead(PIR_OUTB);
  return sensorState;
}
int Get_PIR_IN() {
  int sensorState = digitalRead(PIR_IN);
  return sensorState;
}
float Get_LT_IN() {
  int rawData = analogRead(LDR_IN);
  float voltage = map(rawData, 0, 1023, 0, 5);
  float light = map(voltage, 0, 5, 10, 100);
  return light;
}
float Get_LT_OUT() {
  int rawData = analogRead(LDR_OUT);
  float voltage = map(rawData, 0, 1023, 0, 5);
  float light = map(voltage, 0, 5, 10, 100);
  return light;
}
