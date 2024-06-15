// Shell
#include "Shell.hpp"
int running = 0;          // Указатель на строчку, которая сейчас выполняется
char *line;               // Указатель на строку ввода
char **args;              // Указатель на указатель на аргументы
int vars[26];             // Переменные (a-z)
char program[MAX_SIZE];   // Указатель на буфер исходника программы

// JSON
#include "ArduinoJson.h"

// Temperature DS18B20
//#include "DS18B20.h"
//#define TEMP_OUT 26
//DS18B20 ds18b20(TEMP_OUT);

// Car
#define CAR_LEFT 15
#define CAR_RIGHT 2
#define CAR_FORWARD 3
#define CAR_BACK 4
int car_time = 1000;      // Время работы двигателей

// GPS
/*#include <iarduino_GPS_NMEA.h>             
iarduino_GPS_NMEA gps;
char* wd[]={"Вс","Пн","Вт","Ср","Чт","Пт","Сб"};
int hour_add = 1;
int real_time;
char lat[15];
char lon[15];
char timeGPS[5];
char date[5];*/

// Servo
#include <Servo.h> 
Servo myservo;
#define SERVO 6
int servo_pos = 90;

// Encoder
/*#define ENCODER_DT 3
#define ENCODER_CLK 4
#define pinB 3
#define pinA 4
int pinAstateCurrent = LOW;                // Current state of Pin A
int pinAStateLast = pinAstateCurrent;      // Last read value of Pin A
*/

// 4-Digit
#include "KETM1650.h"
int item = 0;           //display value
#define DIO 16
#define CLK 17
KETM1650 tm_4display(CLK, DIO);
bool is_TEMP_OUT = false;
bool is_TEMP_IN = false;
bool is_HUM = false;
bool is_PHOTORESISTOR = false;
bool is_SERVO = false;

// LCD 128x32
#include "lcd128_32_io.h"
lcd lcd(20, 21);       //sda--->20, scl--->21

// LED
#define LED_TEST 7 
bool is_LED_TEST = false;

// Builtin LED
int led = LED_BUILTIN; // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// Traffic LED
#define LED_GREEN 12   
#define LED_YELLOW 13
#define LED_RED 11
bool is_LED_GREEN = false;
bool is_LED_YELLOW = false;
bool is_LED_RED = true;

// Laser
#define LASER 14
bool is_LASER = false;

// Button
#define BUTTON 18

// Buzzer
#define BUZZER 19

// XHT11
#include "xht11.h"
xht11 xht(22);
unsigned char dht[4] = {0, 0, 0, 0};    // only receive the data before 32 bit

// RTC
/*#include <Wire.h>
#include "RtcDS1307.h" 
RtcDS1307<TwoWire> Rtc(Wire);           // i2c is connected to 14, 15
*/

// Photoresistor
#define PHOTORESISTOR 28                //analog port ADC2 of photoresistor
int photoresistor_val = 0; 


void setup() {
  // Temperature DS18B20
  //pinMode(TEMP_OUT, INPUT_PULLUP);

  // LED
  pinMode(LED_TEST, OUTPUT);

  // Builtin LED
  pinMode(led, OUTPUT);
  
  // Traffic LED
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);

  // Laser
  pinMode(LASER, OUTPUT);

  // Serial
  Serial.begin(9600); 
  Serial1.begin(9600);
  Serial2.begin(9600);

  // Car
  pinMode(CAR_LEFT, OUTPUT);
  digitalWrite(CAR_LEFT, HIGH);
  pinMode(CAR_RIGHT, OUTPUT);
  digitalWrite(CAR_RIGHT, HIGH);
  pinMode(CAR_FORWARD, OUTPUT);
  digitalWrite(CAR_FORWARD, HIGH);
  pinMode(CAR_BACK, OUTPUT);
  digitalWrite(CAR_BACK, HIGH);

  // GPS
  //gps.begin(Serial1);

  // Button
  pinMode(BUTTON, INPUT_PULLDOWN);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // LCD 128x32
  lcd.Init();
  lcd.Clear();

  // 4-Digit
  tm_4display.init();
  tm_4display.setBrightness(3);         // in the range of 1~8

  // Servo
  myservo.attach(SERVO);
  myservo.write(servo_pos);

  // Encoder
//  gpio_set_irq_enabled_with_callback(ENCODER_CLK, GPIO_IRQ_EDGE_FALL, true, &RoteStateChanged);
  //attachInterrupt(interruptA, RoteStateChanged, FALLING);
//  pinMode (ENCODER_CLK, INPUT);
//  digitalWrite(ENCODER_CLK, HIGH);
//  pinMode (ENCODER_DT, INPUT);
//  attachInterrupt(digitalPinToInterrupt(pinB), update, CHANGE);
//  digitalWrite(ENCODER_DT, HIGH);
  //pinMode (ENCODER_Switch, INPUT);
  //Previous_Output = digitalRead(ENCODER_DT);

  // RTC
/*  Rtc.Begin();
  Rtc.SetIsRunning(true);
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
*/
  //Serial2.println(F("Ready."));
  //Serial1.println(F("Ready."));
  Serial.println(F("Ready."));
  lcd.Cursor(0, 0); 
  lcd.Display("Ready.");
  do_beep();
}


void loop() {
  // Builtin LED
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  if(is_PHOTORESISTOR){
    photoresistor_val = analogRead(PHOTORESISTOR);
    //Serial.println(photoresistor_val);
    item = photoresistor_val; 
    tm_4display.displayString(item);
  }

/*  if(is_TEMP_OUT){
    ds18b20.selectNext();
    double tempOut = ds18b20.getTempC();
    //tempOut *= 0.0625;                  //convert to 0.0625/LSB 
    item = tempOut; 
    tm_4display.displayString(item);
  }*/

  if(is_TEMP_IN){
    if(xht.receive(dht)) { 
      item = dht[2]; 
      tm_4display.displayString(item);
    } else {    
      item = 8888;
      tm_4display.displayString(item);
    }
  }

  if(is_HUM){
    if(xht.receive(dht)) { 
      item = dht[0]; 
      tm_4display.displayString(item);
    } else {    
      item = 8888;
      tm_4display.displayString(item);
    }
  }

/*  if(is_SERVO){
    item = servo_pos; 
    tm_4display.displayString(item);
  }*/

  // Encoder
  /*if (digitalRead(ENCODER_DT) != Previous_Output){
    if (digitalRead(ENCODER_CLK) != Previous_Output){
      Encoder_Count ++;
      Serial2.println("<-");
      servo_pos++;
    } else {
      Encoder_Count--;
      servo_pos--;
      Serial2.println("->");
    }
  }
  Previous_Output = digitalRead(ENCODER_DT);
*/

/*  // ROTATION DIRECTION
  pinAstateCurrent = digitalRead(pinA);    // Read the current state of Pin A
  
  // If there is a minimal movement of 1 step
  if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {
    
    if (digitalRead(pinB) == HIGH) {      // If Pin B is HIGH
      Serial2.println("Left");             // Print on screen
      servo_pos--;
    } else {
      Serial2.println("Right");            // Print on screen
      servo_pos++;
    }
    myservo.write(servo_pos);
  }
  
  pinAStateLast = pinAstateCurrent;        // Store the latest read value in the currect state variable
*/

//  myservo.write(servo_pos);
  // Servo
/*  for (int servo_pos = 0; servo_pos < 180; servo_pos++) {
    myservo.write(servo_pos); //rotate to pos
    delay(15);  //
  }
  for (int servo_pos = 180; servo_pos > 0; servo_pos--) {
    myservo.write(servo_pos);
    delay(15);
  }
  delay(2000);//wait for 2s
*/
  //delay(100);

  // Button
  if (digitalRead(BUTTON) == LOW) {
    do_beep(); 
    is_LASER = !is_LASER;
    digitalWrite(LASER, is_LASER);
    delay(100);
  } 

  // GPS
/*  gps.read();                                 
  if(gps.errPos){    
    sprintf(lat, "error"); 
    sprintf(lon, "error");                                                
  }    
  sprintf(lat, "%05f", gps.latitude);
  sprintf(lon, "%05f", gps.longitude);
  if(!gps.errTim){ 
    sprintf(timeGPS, "%02d:%02d", gps.Hours, gps.minutes);
  } else {
    sprintf(timeGPS, "error");
  }
  if(!gps.errDat){        
    sprintf(date, "%02d.%02d.%02d", gps.day, gps.month, gps.year);
  } else {
    sprintf(date, "error");
  }*/

  // Shell
  shell();
}


// Active Buzzer
void do_beep(){
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
}

