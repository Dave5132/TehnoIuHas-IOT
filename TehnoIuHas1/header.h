/*
                            Header written by :
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
*/
//[[Defines]]\\

//[[/Defines]]\\

#ifndef header_h
#define header_h

//[[Libraries]]\\

#include <Arduino.h>
#include <Keypad.h>
#include <Key.h>
#include <LedControl.h>

//[[/Libraries]]\\

//[[Variables]]\\

//matrix codes
const char Characters[]         = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','#','*','X','Y'};
    
const byte MATRIX_DIGITS[]      = {
    {B00000000, B00000000, B00111110, B01000001, B01000001, B00111110, B00000000},
    {B00000000, B00000000, B01000010, B01111111, B01000000, B00000000, B00000000},
    {B00000000, B00000000, B01100010, B01010001, B01001001, B01000110, B00000000},
    {B00000000, B00000000, B00100010, B01000001, B01001001, B00110110, B00000000},
    {B00000000, B00000000, B00011000, B00010100, B00010010, B01111111, B00000000},
    {B00000000, B00000000, B00100111, B01000101, B01000101, B00111001, B00000000},
    {B00000000, B00000000, B00111110, B01001001, B01001001, B00110000, B00000000},
    {B00000000, B00000000, B01100001, B00010001, B00001001, B00000111, B00000000},
    {B00000000, B00000000, B00110110, B01001001, B01001001, B00110110, B00000000},
    {B00000000, B00000000, B00000110, B01001001, B01001001, B00111110, B00000000},
    {B00000000, B00000000, B01111110, B00010001, B00010001, B01111110, B00000000},
    {B00000000, B00000000, B01111111, B01001001, B01001001, B00110110, B00000000},
    {B00000000, B00000000, B00111110, B01000001, B01000001, B00100010, B00000000},
    {B00000000, B00000000 , B01111111, B01000001, B01000001, B00111110, B00000000},
    {B00000000, B00000000, B00010100, B00111110, B00010100, B00111110, B00010100,B00000000},
    {B00000000, B00000000, B00101010, B00011100, B00111110, B00011100, B00101010,B00000000},
    {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},
    {B00000001,B00000011,B00000110,B10001100,B11011000,B01110000,B00100000,B00000000},
    {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111}
};

//[[/Variables]]\\

//[[Main]]\\

class ArduinoHandler{
    //private stuff
    private:
        //passwords 
        const int Password_Length   = 4; // 4 characters allowed
        
        char Room1Password[4]       = {'1','2','3','4'};

    //              functions             \\

    public:
        //function to make the fan to work
        void Turn_on_fan(int FAN_RELAY_PIN){ digitalWrite(FAN_RELAY_PIN,HIGH); }

        //function to turn off the fan
        void Turn_off_fan(int FAN_RELAY_PIN){digitalWrite(FAN_RELAY_PIN,LOW); }

        //function to turn on the buzzer
        void Ring_Buzzer(int BUZZER_PIN){ tone(BUZZER_PIN, 1000); }

        //function to turn off the buzzer
        void Pause_Buzzer(int BUZZER_PIN){ noTone(BUZZER_PIN); }

        //function to set the RGB SMD color to the one given as argument 
        void set_rgb_color(int pins[3],byte color[3]) {
            digitalWrite(pins[0], color[0]);
            digitalWrite(pins[1], color[1]);
            digitalWrite(pins[2], color[2]);
        }

        //function to check the Pir motion sensor's status, returns the bool which is the pir status
        bool check_pir_status(int PIR_SENSOR_PIN) {
            //returning the status
            volatile byte result = digitalRead(PIR_SENSOR_PIN);
            return result = HIGH ? true : false;
        }

        //function to compare the password given as argument to the function with the one in the class,returns a boolean 
        bool CheckPassword(char password[4],String room_name) {
            bool incorrect = false;

            //checking every character through a loop
            for(int increment = 0; increment != 4; increment++){
                incorrect  = password[increment] = Room1Password[increment] ? true : false;
            }
            //returning the value
            return incorrect = true ? true : false;
        }
        
        //function to display a character on the matrix 
        void Display_Character_On_Matrix(LedControl lc , const byte Character){
            volatile byte *List[8];
            
            for(int i = 0; i!=8; i++)
                if(Character == Characters[i])
                    *List = MATRIX_DIGITS[i];
            
            if(Character == "F")
                *List = MATRIX_DIGITS[19];

            if(List) 
                for(int i = 0; i!=8; i++)
                    lc.setRow(0,i,List[i]);
            
        }

        //function to return the amount of characters allowed for a password
        int GetAllowedPasswordLength(){ return Password_Length;}

        //function to light up a led
        void Light_LED(int LED_PIN){
            //lighting up the led bulb
            digitalWrite(LED_PIN,HIGH);
        }
        
        //function to extenguish a led
        void Extinguish_LED(int LED_PIN){
            //shutting down the led bulb
            digitalWrite(LED_PIN,LOW);
        }

        //function to return the distance detected by the ultrasonic sensor
        float get_Ultrasonic_Distance(int ULTRASONIC_TRIG,int ULTRASONIC_ECHO){
            //sending an ultrasonic wave
            digitalWrite(ULTRASONIC_TRIG,HIGH);
            //delaying a bit for the ultrasonic wave to travel
            delayMicroseconds(10);
            
            digitalWrite(ULTRASONIC_TRIG,LOW);

            //returning the calculated distance
            return (pulseIn(ULTRASONIC_ECHO,HIGH) * 0.034)/2;
        }

        //          SETUP FUNCTIONS             \\

        //function to setup the relay
        void RELAY_SETUP(int FAN_RELAY_PIN) {
            //pin for relay module set as output
            pinMode(FAN_RELAY_PIN, OUTPUT);
        }

        //function to setup the pir sensor
        void PIR_SETUP(int PIR_SENSOR_PIN){
            //pir motion sensor set as input
            pinMode(PIR_SENSOR_PIN, INPUT);
        }

        //function to setup the buzzer
        void BUZZER_SETUP(int BUZZER_PIN){
            //pin for buzzer set as output
            pinMode(BUZZER_PIN, OUTPUT);
        }

        //function to setup the smd rgb led
        void RGB_SMD_SETUP(int RGB[3]){
            //setting all the pin modes to output
            pinMode(RGB[0],OUTPUT);

            pinMode(RGB[1],OUTPUT);

            pinMode(RGB[2],OUTPUT);
        }

        //function to setup the led 
        void LED_SETUP(int LED_PIN){
            //setting the pin mode to output
            pinMode(LED_PIN,OUTPUT);
        }

        //function to setup the ultrasonic sensor
        void ULTRASONIC_SETUP(int ULTRASONIC_TRIG,int ULTRASONIC_ECHO){
            pinMode(ULTRASONIC_TRIG,OUTPUT);
            pinMode(ULTRASONIC_ECHO,INPUT);

        }
        //function to setup the keypad, which eventually returns the initialized keypad object to the caller
        Keypad KEYPAD_SETUP(int row_pins[4],int col_pins[4]){
            //creating a map of all the keys
            char HexaKeys[4][4] = {
                {'1','2','3','A'},
                {'4','5','6','B'},
                {'7','8','9','C'},
                {' ','0','#','D'}
            };

            //setting the pin modes to input through a loop
            for(int increment = 0; increment != 4; increment++){
                //setting the pinmode for the column and the row pins
                pinMode(row_pins[increment],INPUT);
                pinMode(col_pins[increment],INPUT);
            }

            //initializing the keypad object
            Keypad keypad = Keypad(makeKeymap(HexaKeys),row_pins,col_pins,4,4);

            //returning the object created
            return keypad;
        }

        //function to setup the matrix 8x8 display, returns the object created
        LedControl MATRIX_SETUP(int DIN, int CS, int CLK){
            //creating the object
            LedControl lc = LedControl(DIN,CLK,CS,0);
            //shutting down the power saving mode
            lc.shutdown(0,false);
            //giving the screen the maximum brightness level
            lc.setIntensity(0,15);
            //cleaning the display
            lc.clearDisplay(0);

            return lc;
        }
};
//[[/Main]]\\

#endif