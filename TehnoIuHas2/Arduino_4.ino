//Panels control
#define LDR_PIN A0
#include <LedControl.h>
#define DIN_1  0
#define CS_1  1
#define CLK_1  2
#define DIN_2  3
#define CS_2  4
#define CLK_2  5
byte night[8] =     {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
byte morning[8] =     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
byte test[8] = {0x18, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E};
LedControl lc_1 = LedControl(DIN_1, CLK_1, CS_1, 0);
LedControl lc_2 = LedControl(DIN_2, CLK_2, CS_2, 0);
char reader;
#define samp_siz 6
#define rise_threshold 7
int sensorPin = 8;
//Buzzer sensor
const int buzzer = 9;
const int buzzer_1 = 10;
const int buzzer_2 = 11;
const int buzzer_3 = 12;
//Flame sensor
int FLAME = A1;
//Leds
int led1 = 13 , led2 = 14;
//light cup sensor
int light_cup1 = 15, light_cup2 = 16;
//Val for light
int val1, val2, plus = 1;
//helper
unsigned long lastMillis1;
void setup() {
  Serial.begin(9600);
  lastMillis1 = millis();
  pinMode(buzzer, OUTPUT);
  pinMode(buzzer_1, OUTPUT);
  pinMode(buzzer_2, OUTPUT);
  pinMode(buzzer_3, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  lc_1.shutdown(0, false);
  lc_1.setIntensity(0, 15);
  lc_1.clearDisplay(0);
  lc_2.shutdown(0, false);
  lc_2.setIntensity(0, 15);
  lc_2.clearDisplay(0);
  pinMode (led1, OUTPUT) ;
  pinMode (light_cup2, INPUT) ;
  pinMode (led2, OUTPUT) ;
  pinMode (light_cup1, INPUT) ;
  pinMode(FLAME, INPUT);
}

void loop() {
  reader = Serial.read();
  switch (reader) {
    case'0':
      plus += 1;
      break;
  }
  if (plus % 2 != 0) {

    Serial.println("Pituh");
    val1 = digitalRead (light_cup1);
    val2 = digitalRead (light_cup1);
    //Read light cup
    if (val1 == 1 && val2 == 1)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
    }
    else
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
    //Read fire sensor
    int fire = analogRead(FLAME);
    if (fire > 100) {
      Serial.println("Fire in the house");
    }
    else {
      Serial.println("Tot e nice");
    }
    //Read water level
    int value = analogRead(A0);
    if (value > 100) {
      tone(buzzer, 1000);
    }
    else {
      noTone(buzzer);
    }
    //Check if is night or day
    if (Get_LT() < 30) {
      printByte_1(test);
      printByte_2(night);
    }
    else {
      printByte_1(night);
      printByte_2(test);
    }
    //Budilnic
    if (millis() - lastMillis1 <= 3000000) {
      noTone(buzzer_1);
      noTone(buzzer_2);
      noTone(buzzer_3);
    }
    else {
      tone (buzzer_1, 1000);
      tone (buzzer_2, 1000);
      tone (buzzer_3, 1000);
      delay(5000);
      lastMillis1 = millis();
    }
  }
  else {
    //  //Health beat sensor reading
    float reads[samp_siz], sum;
    long int now, ptr;
    float last, reader, start;
    float first, second, third, before, print_value;
    bool rising;
    int rise_count;
    int n;
    long int last_beat;
    for (int i = 0; i < samp_siz; i++)
      reads[i] = 0;
    sum = 0;
    ptr = 0;
    while (1)
    {
      n = 0;
      start = millis();
      reader = 0.;
      do
      {
        reader += analogRead (sensorPin);
        n++;
        now = millis();
      }
      while (now < start + 20);
      reader /= n;
      sum -= reads[ptr];
      sum += reader;
      reads[ptr] = reader;
      last = sum / samp_siz;
      if (last > before)
      {
        rise_count++;
        if (!rising && rise_count > rise_threshold)
        {
          rising = true;
          first = millis() - last_beat;
          last_beat = millis();
          print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
          Serial.print(print_value);
          Serial.print('\n');
          third = second;
          second = first;
        }
      }
      else
      {
        rising = false;
        rise_count = 0;
      }
      before = last;
      ptr++;
      ptr %= samp_siz;
    }
  }


}
float Get_LT() {
  int rawData = analogRead(LDR_PIN);
  float voltage = map(rawData, 0, 1023, 0, 5);
  float light = map(voltage, 0, 5, 10, 100);
  return light;
}
void printByte_1(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc_1.setRow(0, i, character[i]);
  }
}
void printByte_2(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc_2.setRow(0, i, character[i]);
  }
}
