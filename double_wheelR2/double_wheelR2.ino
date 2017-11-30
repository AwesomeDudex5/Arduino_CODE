// Code tuned for robot 2
// modified: 10/03/2017, Houman Dallali
// COMP 590

#include <Servo.h>
// #define ROTATION 663 // According to manual
#define ROTATION 280  // According to tests?

// encoder variables:
const byte encoder0pinA = 2;//2;//A pin -> the interrupt pin 2
const byte encoder0pinB = 3;//3;//B pin -> the digital pin 3

const byte encoder1pinA = 18;//18;//A pin -> the interrupt pin 18
const byte encoder1pinB = 19;//19;//B pin -> the digital pin 19

// encoder0
int encoder0PinA = 2;
int encoder0PinB = 3;
volatile int encoder0Pos = 0;
volatile int encoder0PinALast = LOW;
volatile int n = LOW;
int valNew = 0;
int valOld = 0;
volatile int m = LOW;

// encoder1
int encoder1PinA = 18;
int encoder1PinB = 19;
volatile int encoder1Pos = 0;
volatile int encoder1PinALast = LOW;
volatile int n1 = LOW;
int valNew1 = 0;
int valOld1 = 0;
volatile int m1 = LOW;

int loopCnt=0;
int Ts = 1; //1ms

float desiredTurns = 2;

int duration0;//the number of the pulses
boolean Direction0;//the rotation Direction0 


int duration1;//the number of the pulses
boolean Direction1;//the rotation Direction0 

#define CIRC 136 * PI
#define PIP_DIST (CIRC) / ROTATION

int power0, power1;

Servo ST1, ST2; 
void setup()
{
  ST1.attach( 10, 1000, 2000);
  ST2.attach(9, 1000, 2000);

  power0 = 90;
  power1 = 90;
  Serial.begin (9600);
  
  Direction0 = true;//default -> Forward
  Direction1 = true;//default -> Forward   
  pinMode (encoder0PinA,INPUT); 
  pinMode (encoder1PinA,INPUT); 
  pinMode(encoder0pinB,INPUT);
  pinMode(encoder1pinB,INPUT);  
  attachInterrupt(digitalPinToInterrupt(encoder0pinA), wheelSpeed0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1pinA), wheelSpeed1, CHANGE);

}

void loop()
{
  int distance = 1000;

    // proportional feedback gain:
    int kp=10;
        
    float turns0    = ((float)encoder0Pos)/ROTATION;
    float turns1    = ((float)encoder1Pos)/ROTATION;

    Serial.print("Encoder Pos ");
    Serial.print(encoder0Pos);
    Serial.print(" ");
    Serial.print(encoder1Pos);
    Serial.println(" ");

    desiredTurns = 2;   

    //do one full turn
    int durationPip = PIP_DIST * duration0;
    
    if((durationPip) <= distance){
    //if(duration0 < desiredTurns){
    power1=96; //Wheel 2
    power0=78; //Wheel 1
    // sending the control with PWM 
    }
    else
    {
      power0 = 90;
      power1 = 90;      
      .
    }
    ST1.write(power0);
    ST2.write(power1);

    Serial.print("Turns ");
    Serial.print(turns0);
    Serial.print(" ");
    Serial.print(turns1);
    Serial.print(" ");
    Serial.print(durationPip);
    Serial.println(" ");
    
//E N C O D E R  S T U F F
  encoder0PinALast = n;
  valNew = encoder0Pos;
  if (valNew != valOld) {
    valOld = valNew;
  }

  encoder1PinALast = n1;
  valNew1 = encoder1Pos;
  if (valNew1 != valOld1) {
    valOld1 = valNew1;
  }
   
  loopCnt++;  
  
}


void moveForward(int distance, int durationPip)
{
  while(durationPip <= distance)
  {
    power0=95; //Wheel 1
    power1=78; //Wheel 2
  }

  //Stop
  power0 = 90;
  power1 = 90;      
}

void moveBackward()
{
  
}

void turningLeft()
{
  
}

void turningRight()
{
  
}

void wheelSpeed0()
{
  int Lstate0 = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate0==HIGH)
  {
    int val0 = digitalRead(encoder0pinB);
    if(val0 == LOW && Direction0)
      Direction0 = false; //Reverse
    else if(val0 == HIGH && !Direction0)
      Direction0 = true;  //Forward
  }
  encoder0PinALast = Lstate0;
  
  if(!Direction0)  duration0++;
  else  duration0--;

}

void wheelSpeed1()
{
  int Lstate1 = digitalRead(encoder1pinA);
  if((encoder1PinALast == LOW) && Lstate1==HIGH)
  {
    int val1 = digitalRead(encoder1pinB);
    if(val1 == LOW && Direction1)
      Direction1 = false; //Reverse
    else if(val1 == HIGH && !Direction1)
      Direction1 = true;  //Forward
  }
  encoder1PinALast = Lstate1;
  
  if(!Direction1)  duration1++;
  else  duration1--;
   
}
