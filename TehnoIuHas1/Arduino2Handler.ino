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

                            responsable for garage
*/
//[[Defines]]\\

#define PIR_SENSOR_PIN 0
#define BUZZER_PIN 0
#define ULTRASONIC_TRIG 0 
#define ULTRASONIC_ECHO 0
#define RECEIVER_PIN 0
//[[/Defines]]\\

//[[Libraries]]\\

#include <Arduino.h>
#include <header.h>
#include <SevSeg.h>
#include <IRremote.h>
#include <Stepper.h>

//[[/Libraries]]\\

//[[Variables]]\\

// booleans

bool isHouseOpen                 = true;
bool Anti_Theft_Trigerred        = false;
bool motor_direction             = true;
// floats

float ultrasonic_distance        = 0;

//rgb smd pin list {RED,GREEN,BLUE}
byte RGB_SMD_PINS[3]             = {0,0,0};

//colors 
byte Purple[3]                   = {1,0,1};
byte Turquoise[3]                = {0,1,1};
byte Nothing[3]                  = {0,0,0};
byte Blue[3]                     = {0,0,1};
byte Red[3]                      = {1,0,0};

byte PIR_STATE                   = LOW;

// constants
const int DELAY_TIME             = 100; // milliseconds = 0.1 sec which is the cooldown
const int DIGIT_PINS[]           = {0,0,0,0}; // digit pins
const int SEGMENT_PINS[]         = {0,0,0,0,0,0,0}; // segment pins for the digit
const int StepsPerRevolution     = 200;
const int STEPPER_PINS[]         = {0,0,0,0};

// objects

ArduinoHandler arduino;
SevSeg digit_display;
IRrecv irrecv(RECEIVER_PIN);
decode_results results;
Stepper StepperMotor(StepsPerRevolution,STEPPER_PINS[0],STEPPER_PINS[1],STEPPER_PINS[2],STEPPER_PINS[3]);

//[[/Variables]]\\

//[[Functions]]\\

//function to turn off the anti theft system
void Turn_off_Anti_Theft(){
    arduino.Pause_Buzzer(BUZZER_PIN);
    arduino.set_rgb_color(RGB_SMD_PINS,Nothing);
}

//function to turn on the anti theft system
void Turn_on_Anti_Theft(){
    arduino.Ring_Buzzer(BUZZER_PIN);
    arduino.set_rgb_color(RGB_SMD_PINS,Red);
}


//[[/Functions]]\\

//          MAIN           \\

void setup() {
    //calling all the setup functions

    arduino.PIR_SETUP(PIR_SENSOR_PIN);

    arduino.BUZZER_SETUP(BUZZER_PIN);

    arduino.RGB_SMD_SETUP(RGB_SMD_PINS);

    arduino.ULTRASONIC_SETUP(ULTRASONIC_TRIG,ULTRASONIC_ECHO);
    
    digit_display.begin(COMMON_ANODE, 4, DIGIT_PINS, SEGMENT_PINS, true, false, false, false);
    digit_display.setBrightness(100); //setting the brightness to maximum level
    
    irrecv.enableIRIn();

    StepperMotor.setSpeed(60);

    Serial.begin(9600);
}

void loop() {
    
    //      MONITORING ACTIVITY       \\

    //checking if the pir detects any motion
    if(arduino.check_pir_status(PIR_SENSOR_PIN)){
        //checking the pir state variable to make sure we dont spam the entire program when motion is detected
        if(PIR_STATE == LOW){
            //updating the variable's value
            PIR_STATE = HIGH;

            //checking if the house is open and the anti theft system hasn't been trigerred
            if(!isHouseOpen && !Anti_Theft_Trigerred){
                //trigerring the anti theft system
                Turn_on_Anti_Theft();
                Anti_Theft_Trigerred = true;
            //checking if the house is open and the anti theft system has been triggered
            }else if(isHouseOpen && Anti_Theft_Trigerred){
                //lighting up the rgb led 
                arduino.set_rgb_color(RGB_SMD_PINS,Blue);
                //shutting down the anti theft system
                Turn_off_Anti_Theft();
            }
        }else{
            //updating the variable's value
            PIR_STATE = LOW;

            //shutting down the rgb led
            arduino.set_rgb_color(RGB_SMD_PINS,Nothing);
        }
    }

    //checking the distance detected by the ultrasonic
    ultrasonic_distance = round(arduino.get_Ultrasonic_Distance(ULTRASONIC_TRIG,ULTRASONIC_ECHO));

    if(ultrasonic_distance <= 50){
        //checking if the house is locked
        if(!isHouseOpen)
            Turn_on_Anti_Theft();
        else{
            digit_display.setNumber(ultrasonic_distance); //printing the value 
            digit_display.refreshDisplay(); // refreshing the display
        }
    }else{
        //cleaning the screen
        digit_display.blank();
    }

    if (irrecv.decode(&results)) {
        if(motor_direction){
            StepperMotor.step(StepsPerRevolution);
            motor_direction = false;
        }else{
            StepperMotor.step(-StepsPerRevolution);
            motor_direction = true;
        }
        irrecv.resume();
    }

    delay(DELAY_TIME);
}
