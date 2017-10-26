/*
Pay attention to the interrupt pin,please check which microcontroller you use.
http://arduino.cc/en/Reference/AttachInterrupt
*/
 
//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 2
const byte encoder0pinB = 3;//B pin -> the digital pin 3
byte encoder0PinALast;
int duration;//the number of the pulses
boolean Direction;//the rotation direction 

#include <Servo.h>

Servo ST1, ST2;

void setup()
{  
  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  
  ST1.attach( 9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  
}
  
void loop()
{
  Serial.print("Pulse:");
  Serial.println(duration);
  duration = 0;
  ST1.write(85);
  ST2.write(84+8);
  delay(10);
}
  
void EncoderInit()
{
  Direction = true;//default -> Forward  
  pinMode(encoder0pinB,INPUT);  
  //attachInterrupt(digitalPinToInterrupt(2), wheelSpeed, CHANGE);//int.on pin 18
  attachInterrupt(digitalPinToInterrupt(18), wheelSpeed, CHANGE);//int.on pin 18
}
  
void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction)
    {
      Direction = false; //Reverse
    }
    else if(val == HIGH && !Direction)
    {
      Direction = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;
  
  if(!Direction)  duration++;
  else  duration--;
}
