//Librarii
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <dht11.h>
int x = 0, y = 0, t = 9, x_b = 0, y_b = 0, t_b = 0;
char* password = "2402";
//KeyPad_Front//
const byte rows_F = 4;
const byte cols_F = 4;
char keyMap_F [rows_F] [cols_F] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins_F[rows_F] = {7, 6, 5, 4};
byte colPins_F[cols_F] = {3, 2, 1, 0};
Keypad myKeypad_F = Keypad( makeKeymap(keyMap_F), rowPins_F, colPins_F, rows_F, cols_F);
//KeyPad_Back//
const byte rows_B = 4;
const byte cols_B = 4;
char keyMap_B [rows_B] [cols_B] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins_B[rows_B] = {15, 14, 13, 12};
byte colPins_B[cols_B] = {11, 10, 9, 8};
Keypad myKeypad_B = Keypad( makeKeymap(keyMap_B), rowPins_B, colPins_B, rows_B, cols_B);
//Servo//
Servo Servo_OUTF, Servo_OUTB_L, Servo_OUTB_R, Servo_IN;
//LCD//
LiquidCrystal lcd_B (A0, A1, A2, A3, A4, A5);
LiquidCrystal lcd_F (A6, A7, A8, A9, A10, A11);
//Fan//
#define fan1 16
#define fan2 17
#define fan3 18
//Temperature and Humidity//
#define dht_apin A12
#define dht_bpin A13
#define dht_cpin A14
#define dht_dpin A15
dht11 DHT11, DHT22, DHT33, DHT44;
//Read from wer
char reader;
//Time for doors
int interval, time_b;
//Door and fan control
int door_1 = 1, door_2 = 1, door_3 = 1, door_4 = 1, fan_1 = 1, fan_2 = 1, fan_3 = 1, auto_1 = 1;
//Touch senzor
#define touchPIN 19
//Millis
unsigned long lastMillis1;
unsigned long lastMillis2;
unsigned long lastMillis3;
unsigned long lastMillis4;
unsigned long lastMillis5;
unsigned long lastMillis6;
unsigned long lastMillis7;
unsigned long lastMillis8;

char str[] = "";
void setup() {
  lcd_B.begin(16, 2);
  lcd_F.begin(16, 2);
  Serial.begin(9600);
  Servo_OUTF.attach(0);
  Servo_OUTB_L.attach(3);
  Servo_OUTB_R.attach(1);
  Servo_IN.attach(13);
  lastMillis1 = millis();
  lastMillis2 = millis();
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(touchPIN, INPUT);
  Servo_OUTF.write(20);
  Servo_OUTB_L.write(20);
  Servo_OUTB_R.write(20);
  Servo_IN.write(20);
  delay(1000);
  Servo_OUTF.write(110);
  Servo_OUTB_L.write(110);
  Servo_OUTB_R.write(110);
  Servo_IN.write(110);
  delay(1000);
  lastMillis1 = millis();
  lastMillis2 = millis();
  lastMillis3 = millis();
  lastMillis4 = millis();
  lastMillis5 = millis();
  lastMillis6 = millis();
  lastMillis7 = millis();
  lastMillis8 = millis();
}

void loop() {
  Serial.println("est");
  DHT11.read(dht_apin);
  DHT22.read(dht_bpin);
  DHT33.read(dht_cpin);
  DHT44.read(dht_dpin);
  int touchState = digitalRead(touchPIN);
  //Read from wed
  reader = Serial.read();
  switch (reader) {
    case '0':
      door_1 += 1;
      break;
    case '1':
      door_2 += 1;
      break;
    case '2':
      door_3 += 1;
      break;
    case '3':
      door_4 += 1;
      break;
    case '4':
      fan_1 += 1;
      break;
    case '5':
      fan_1 += 1;
      break;
    case '6':
      fan_1 += 1;
      break;
    case '7':
      auto_1 += 1;
      break;
  }

  //Manual or auto control
  if (auto_1 % 2 == 0) {
    //Manual
    char str[] = "Manual_On";
    if (fan_1 % 2 == 0) {
      digitalWrite(fan1, HIGH);
      char str[] = "Fan1_On";
    }
    else {
      digitalWrite(fan1, LOW);
      char str[] = "Fan1_OFF";
    }
    if (fan_2 % 2 == 0) {
      digitalWrite(fan2, HIGH);
      char str[] = "Fan2_On";
    }
    else {
      digitalWrite(fan2, LOW);
      char str[] = "Fan2_OFF";
    }
    if (fan_3 % 2 == 0) {
      digitalWrite(fan3, HIGH);
      char str[] = "Fan3_On";
    }
    else {
      digitalWrite(fan3, LOW);
      char str[] = "Fan3_OFF";
    }
    if (door_1 % 2 == 0) {
      Servo_OUTF.write(20);
      char str[] = "Door1_Open";
    }
    else {
      Servo_OUTF.write(110);
      char str[] = "Door1_Close";
    }
    if (door_2 % 2 == 0) {
      Servo_OUTB_L.write(20);
      char str[] = "Door2_Open";
    }
    else {
      Servo_OUTB_L.write(110);
      char str[] = "Door2_Close";
    }
    if (door_3 % 2 == 0) {
      Servo_OUTB_R.write(20);
      char str[] = "Door3_Open";
    }
    else {
      Servo_OUTB_R.write(110);
      char str[] = "Door3_Close";
    }
    if (door_4 % 2 == 0) {
      Servo_IN.write(20);
      char str[] = "Door4_Open";
    }
    else {
      Servo_IN.write(110);
      char str[] = "Door4_Close";
    }

  }
  else {
    char str[] = "Manual_Off";
    //Auto
    if (DHT11.temperature >= 40) {
      digitalWrite(fan1, HIGH);
      char str[] = "Fan1_On";
    }
    else {
      digitalWrite(fan1, LOW);
      char str[] = "Fan1_OFF";
    }
    //Fan 2
    if (DHT22.temperature >= 34) {
      digitalWrite(fan2, HIGH);
      char str[] = "Fan2_On";
    }
    else {
      digitalWrite(fan2, LOW);
      char str[] = "Fan2_OFF";
    }
    //Fan 3
    if (DHT33.temperature >= 34) {
      digitalWrite(fan3, HIGH);
      char str[] = "Fan3_On";
    }
    else {
      digitalWrite(fan3, LOW);
      char str[] = "Fan3_OFF";
    }
  }
  //start read keypad
  char whichKey_F = myKeypad_F.getKey();
  char whichKey_B = myKeypad_B.getKey();
  //Read from front keypad
  if (whichKey_F == password[x]) {
    x++;
  }
  if (whichKey_F == '1' || whichKey_F == '2' || whichKey_F == '3' || whichKey_F == '5' || whichKey_F == '6' || whichKey_F == '7' || whichKey_F == '8' || whichKey_F == '9' || whichKey_F == '0' || whichKey_F == '4') {
    y++;
    lcd_F.setCursor(t, 1);
    lcd_F.write(whichKey_F);
    t++;
  }
  //Check if is corrent or no
  if (x == 4) {
    lastMillis2 = millis();
    lcd_F.clear();
    y = 0;
    x = 0;
    t = 9;
    char str[] = "Door1_Open";
    interval = 7000;
    lastMillis3 = millis();
  }
  else if (y == 4) {
    lcd_F.clear();
    lastMillis1 = millis();
    interval = 2000;
    lastMillis3 = millis();
    y = 0;
    x = 0;
    t = 9;
  }
  //Open door
  if (millis() - lastMillis2 <= 7000) {
    lcd_F.setCursor(0, 1);
    lcd_F.print("Welcome");
    Servo_OUTF.write(110);
  }
  else {
    Servo_OUTF.write(20);
  }
  //Say try again the code
  if (millis() - lastMillis1 <= 2000) {
    lcd_F.setCursor(0, 1);
    lcd_F.print("Try Again");
  }
  //Reload the lcd and write again password
  if (millis() - lastMillis3 <= interval) {
  }
  else {
    lcd_B.setCursor(0, 0);
    lcd_B.print("Enter Password");
    lcd_B.setCursor(0, 1);
    lcd_B.print("Password:");
  };





  //Read from back keypad
  if (whichKey_B == password[x]) {
    x_b++;
  }
  if (whichKey_B == '1' || whichKey_B == '2' || whichKey_B == '3' || whichKey_B == '5' || whichKey_B == '6' || whichKey_B == '7' || whichKey_B == '8' || whichKey_B == '9' || whichKey_B == '0' || whichKey_B == '4' || whichKey_B == 'B' || whichKey_B == 'A' | whichKey_B == 'D' || whichKey_B == 'C') {
    y_b++;
    lcd_B.setCursor(t_b, 1);
    lcd_B.write(whichKey_B);
    t_b++;
  }
  //  if (x_b == 4) {
  //    lastMillis5 = millis();
  //    lcd_B.clear();
  //    y_b = 0;
  //    x_b = 0;
  //    t_b = 9;
  //    time_b = 7000;
  //    lastMillis6 = millis();
  //
  //  }
  //Chekc the password if this is corect and if the door are selected corect

  if (whichKey_B == 'A' && x_b == 4) {
    lastMillis5 = millis();
    char str[] = "Door2_Open";
    lcd_B.clear();
    y_b = 0;
    x_b = 0;
    t_b = 9;
    time_b = 7000;
    lastMillis6 = millis();
  }
  else if (whichKey_B == 'B' && x_b == 4) {
    lastMillis7 = millis();
    char str[] = "Door3_Open";;
    lcd_B.clear();
    y_b = 0;
    x_b = 0;
    t_b = 9;
    time_b = 7000;
    lastMillis6 = millis();
  }
  else if (y_b == 5) {
    lcd_B.clear();
    lastMillis4 = millis();
    time_b = 2000;
    lastMillis3 = millis();
    y_b = 0;
    x_b = 0;
    t_b = 9;
  }
  //open left door
  if (millis() - lastMillis5 <= 7000) {
    lcd_B.setCursor(0, 1);
    lcd_B.print("Welcome");
    Servo_OUTB_L.write(110);
  }
  else {
    Servo_OUTB_L.write(20);
  }
  //open right door
  if (millis() - lastMillis7 <= 7000) {
    lcd_B.setCursor(0, 1);
    lcd_B.print("Welcome");
    Servo_OUTB_R.write(110);
  }
  else {
    Servo_OUTB_R.write(20);
  }


  if (millis() - lastMillis4 <= 2000) {
    lcd_B.setCursor(0, 1);
    lcd_B.print("Try Again");
  }
  //try again the password
  if (millis() - lastMillis6 <= time_b) {
  }
  else {
    lcd_B.setCursor(0, 0);
    lcd_B.print("Enter Password");
    lcd_B.setCursor(0, 1);
    lcd_B.print("Password:");
  }
  //check info from touch sensor and open door
  if (touchState == 1) {
    char str[] = "Door4_Open";
    lastMillis8 = millis();
  }

  if (millis() - lastMillis8 <= 7000) {
    Servo_IN.write(20);
  }
  else {
    Servo_IN.write(110);
  }
  //Sent to wed info

  Serial.print("row:"); Serial.print(DHT11.temperature); Serial.print("C "); Serial.print(DHT11.humidity); Serial.print("H ") ;  Serial.print(DHT44.temperature); Serial.print("C "); Serial.print(DHT44.humidity); Serial.print("H "); Serial.print("log:"); Serial.print(str); Serial.println();

}
