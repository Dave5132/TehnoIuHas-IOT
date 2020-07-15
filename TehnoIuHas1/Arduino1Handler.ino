/*
                            Program written by :
                                             __      __                              __     
                                            /\ \  __/\ \                            /\ \
                                            \ \ \/\ \ \ \     __   __  __    ___    \_\ \   
                                             \ \ \ \ \ \ \  /'__`\/\ \/\ \ /' _ `\  /'_` \  
                                              \ \ \_/ \_\ \/\ \_\ \ \ \_\ \/\ \/\ \/\ \_\ \ 
                                               \ `\___x___/\ \___, \ \____/\ \_\ \_\ \___,_\
                                                '\/__//__/  \/___/\ \/___/  \/_/\/_/\/__,_ /
                                                                 \ \_\                      
                                                                  \/_/                      
                            Contact me :  
                                Discord : PirateDev#4309 or PirateDev#0001

                            responsable for Room1
*/

//[[Libraries]]\\

#include <Arduino.h>
#include <header.h>
#include <Keypad.h>
#include <Key.h>
#include <LedControl.h>


//[[/Libraries]]\\

//[[Defines]]\\

#define FAN_RELAY_PIN 24
#define PIR_SENSOR_PIN 46
#define BUZZER_PIN 24
#define MATRIX_DIN 0
#define MATRIX_CLK 0
#define MATRIX_CS 0

//[[/Defines]]\\

//[[Variables]]\\

ArduinoHandler arduino;

// booleans
bool isHouseOpen                 = false;

// integers
long int Last_Debounce_Time      = 0;
int Password_Length              = arduino.GetAllowedPasswordLength()-1;
int Password_Character_Count     = 0;
int Wrong_Password_Count         = 0;
int Last_Time_Introduced_Wrong_Password = 0;

//rgb smd pin list {RED,GREEN,BLUE}
byte RGB_SMD_PINS[3]             = {0,0,0};

//colors 
byte Purple[3]                   = {1,0,1};
byte Turquoise[3]                = {0,1,1};
byte Nothing[3]                  = {0,0,0};
byte Blue[3]                     = {0,0,1};
byte Red[3]                      = {1,0,0};

// constants
const int DELAY_TIME             = 100; // milliseconds = 0.1 sec which is the cooldown

// arrays
int KEYPAD_ROW_PINS[4]           = {0,0,0,0};
int KEYPAD_COL_PINS[4]           = {0,0,0,0};

const int MATRIX_ROW_PINS[8]     = {0,0,0,0,0,0,0,0};
const int MATRIX_COL_PINS[8]     = {0,0,0,0,0,0,0,0};

// chars

char Introduced_Password[4]      = {};

// objects

//initializing the keypad
Keypad keypad                    = arduino.KEYPAD_SETUP(KEYPAD_ROW_PINS,KEYPAD_COL_PINS);

//initializing the 8x8 matrix display
LedControl Matrix                = arduino.MATRIX_SETUP(MATRIX_DIN,MATRIX_CLK,MATRIX_CS);

//[[/Variables]]\\

//[[Functions]]\\

void DeletePasswordData(){
    Password_Character_Count = 0;
    //if the 100 seconds passed since last time a wrong combination of a password was introduced, then we delete the wrong password count data
    if(Last_Time_Introduced_Wrong_Password - millis() >= 100000) Wrong_Password_Count = 0;
    for(int i =  0; i!=Password_Length;i++)
        Introduced_Password[i] = ' ';
}

//function to turn off the anti theft system
void Turn_off_Anti_Theft(){
    arduino.Pause_Buzzer(BUZZER_PIN);
    arduino.set_rgb_color(RGB_SMD_PINS,Nothing);
    Matrix.clearDisplay(0);
}

//function to turn on the anti theft system
void Turn_on_Anti_Theft(){
    arduino.Ring_Buzzer(BUZZER_PIN);
    arduino.set_rgb_color(RGB_SMD_PINS,Red);
    arduino.Display_Character_On_Matrix(Matrix,"F");
}

//[[/Functions]]\\

//          MAIN           \\

void setup() {
    //calling all the setup functions
    arduino.RELAY_SETUP(FAN_RELAY_PIN);

    arduino.PIR_SETUP(PIR_SENSOR_PIN);

    arduino.BUZZER_SETUP(BUZZER_PIN);

    arduino.RGB_SMD_SETUP(RGB_SMD_PINS);

    Serial.begin(9600);
}

void loop() {
    //      MONITORING ACTIVITY       \\
    //checking the pir status
    if(arduino.check_pir_status(PIR_SENSOR_PIN)) {
        //checking if the house is open
        if(!isHouseOpen) {
            //if the pir returns true and the house is locked, then we toggle all the anti-theft systems
            Turn_on_Anti_Theft();
        }else{
            //turning on the light to the color blue
            arduino.set_rgb_color(RGB_SMD_PINS,Blue);
            //turning on the fan
            arduino.Turn_on_fan(FAN_RELAY_PIN);
        }
    }else{
        //turning of the light since there is no activity
        arduino.set_rgb_color(RGB_SMD_PINS,Nothing);
        //turning off the fan
        arduino.Turn_off_fan(FAN_RELAY_PIN);
    }

    //monitoring the keypad
    char Key = keypad.getKey();

    if(Key && !isHouseOpen)
        Turn_on_Anti_Theft();
    else {

        if(Password_Character_Count < Password_Length){
            arduino.Display_Character_On_Matrix(Matrix,Key);

            Introduced_Password[Password_Character_Count] = Key;

            Password_Character_Count++;
        }else if (Password_Character_Count == Password_Length){

            char incorrect = arduino.CheckPassword(Introduced_Password,"Room1");

            if(incorrect){
                //this code runs if the password combination is incorrect
                Wrong_Password_Count++;
                arduino.Display_Character_On_Matrix(Matrix,'X');

                //turning on the anti theft system if the password was introduced wrong more than 3 times
                if(Wrong_Password_Count >= 3) 
                    Turn_on_Anti_Theft();
                
            }else{
                //this code runs if the password combination is correct
                arduino.Light_LED(0);
                arduino.Display_Character_On_Matrix(Matrix,'Y');
                delay(3000);
                arduino.Extinguish_LED(0);
            }
        }
    }

    Matrix.clearDisplay(0);
    DeletePasswordData();

    if(isHouseOpen)
        //turning off the anti theft system since the house is unlocked now
        Turn_off_Anti_Theft();
    
    //delaying 1 second
    delay(DELAY_TIME);
}
