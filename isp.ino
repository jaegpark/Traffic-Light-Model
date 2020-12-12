#include <Servo.h>

//timing variables for traffic light x 2 and pedestrian light
int greenTime = 2000;
int yellowTime = 1000;
int redTime = 2000;

//controls the two sets of traffic lights and pedestrian red
int red1 = 13;
int yellow1 = 12;
int green1 = 11;

//controls one set of traffic lights
int red2 = 10;
int yellow2 = 9;
int green2 = 8;

//pedestrian green
int green3 = 7;

//street light led
int ledPin =  2;
int ledLevel = 0;

//LDR sensor port
int ldrPin = A0;
int ldrStatus = 0;

//button pin
int buttonPin = 3;
int buttonState = 0;   
int buttonPressed = 0;

//servo motor
Servo servo;
int pos = 0;

//IR sensor
int IRPin = A5;
int IRLedPin = 6;

void setup() { 
  Serial.begin(9600);
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode (ledPin, OUTPUT);
  pinMode (ldrPin, INPUT);
  pinMode(IRPin, INPUT);
  pinMode(IRLedPin, OUTPUT);
  servo.attach(5);
}

void loop() {
  digitalWrite(IRLedPin, HIGH);
  servo.write(0);
  digitalWrite(yellow1, LOW);
  digitalWrite (red2, LOW);
  digitalWrite(green3, LOW);
  digitalWrite(red1, HIGH); 
  digitalWrite(green2, HIGH);  
  pause(redTime, 1);
  digitalWrite(green2, LOW); 
  digitalWrite(yellow2, HIGH); 
  pause(yellowTime, 2);
  resetTime (); 
  digitalWrite(yellow2, LOW);
  digitalWrite(red1, LOW); 
  digitalWrite(red2, HIGH); 
  digitalWrite(green3, HIGH);
  digitalWrite(green1, HIGH); 
  servo.write(180);
  pause(greenTime, 0); 
  resetTime ();
  digitalWrite(green1, LOW); 
  digitalWrite(yellow1, HIGH); 
  pause(yellowTime, 2); 
}

void checkLDR()
{
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 10) {
  digitalWrite(ledPin, HIGH);
  } else {
  digitalWrite(ledPin, LOW);
  }
}

void checkButton ()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && buttonPressed == 0) {
    greenTime = greenTime + greenTime/2;
    yellowTime = yellowTime/2;
    redTime = redTime/2;
    buttonPressed = 1;
  } else if (buttonState == HIGH && buttonPressed == 1) {
  }
  else if (buttonState == LOW) {
    buttonPressed = 0;
  }
}

void checkIR ()
{
  int value = analogRead (IRPin);
  Serial.println(value);
  if (value <120)
    Serial.println ("Car");
  else
    Serial.println ("No car");
    
}

void pause (int time, int colour)
{
  //0 is green, 1 is red, 2 is yellow
  for (int i = 1; i <= time; i+=20)
  {
    delay (20); 
    checkIR();
    checkLDR();
    checkButton();
    if (colour == 0){
      time = greenTime;}
    else if (colour == 1){
      time = redTime;    
    }
    else if (colour == 2){
      time = yellowTime;  
    }
  }
}

void resetTime ()
{
  greenTime = 2000;
  yellowTime = 1000;
  redTime = 2000;
}
