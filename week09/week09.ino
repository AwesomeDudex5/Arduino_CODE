 
//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//2;//A pin -> the interrupt pin 2
const byte encoder0pinB = 3;//3;//B pin -> the digital pin 3

const byte encoder1pinA = 9;//18;//A pin -> the interrupt pin 18
const byte encoder1pinB = 10;//19;//B pin -> the digital pin 19

byte encoder0PinALast;
int duration0;//the number of the pulses
boolean Direction0;//the rotation Direction0 

byte encoder1PinALast;
int duration1;//the number of the pulses
boolean Direction1;//the rotation Direction0 

int loops;

#include <Servo.h>

//#define ROTATION 663 // According to manual
//#define ROTATION 398  // According to tests?
#define ROTATION 315 //1326?????

#define CIRC 136 * PI

#define PIP_DIST (CIRC) / ROTATION


#define PRINT_EVERY 5000//25 

#define ENC_0_NEG_SLOW 90
#define ENC_0_NEG_FAST 180//180  

#define ENC_0_POS_SLOW 80
#define ENC_0_POS_FAST 0//0

Servo ST0, ST1;

void setup()
{  
  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  
  ST0.attach( 9, 1000, 2000);
  ST1.attach(10, 1000, 2000);

  loops = 0;

  ST0.write(60);
  ST1.write(60);
  //delay(10); 
}
  
void loop()
{
  Drive(1000);
}

void Drive(int distance){
  if(duration0 * PIP_DIST >= distance * 2){
    Serial.print(duration0);
    Serial.print(" ");
    Serial.println(duration1);
    ST0.write(85);
    ST1.write(85);
    delay(10);   
  }
}
  
void EncoderInit()
{
  Direction0 = true;//default -> Forward
  Direction1 = true;//default -> Forward   
  pinMode(encoder0pinB,INPUT);
  pinMode(encoder1pinB,INPUT);  
  attachInterrupt(digitalPinToInterrupt(encoder0pinA), wheelSpeed0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1pinA), wheelSpeed1, CHANGE);
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
