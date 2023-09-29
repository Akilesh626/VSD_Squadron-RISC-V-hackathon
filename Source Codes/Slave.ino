#include <SoftwareSerial.h>


// MOTOR A CONTROL PINS (Left motor)
int speedpinA = 3;  
int directionA1 = 4;
int directionA2 = 5;


//MOTOR B CONTROL PINS (Right motor)
int speedpinB = 6;
int directionB1 = 7;
int directionB2 = 8;

//Initial Motor Speed
int motorSpeed = 60;
int maintainSpeed = 0;


//Received Command
char state;

//Direction Status
bool dirA1;
bool dirA2;
bool dirB1;
bool dirB2;

SoftwareSerial Bt(2, 3);  // RX, TX

void setup() 
{
  // Bluetooth Initialisation
  Serial.begin(38400);  // Serial monitor for debugging
  Bt.begin(38400);  // Bluetooth module communication speed

  // Setting pin modes of the L298N Motor Driver
  pinMode(speedpinA, OUTPUT);
  pinMode(directionA1, OUTPUT);
  pinMode(directionA2, OUTPUT);
  pinMode(speedpinB, OUTPUT);
  pinMode(directionB1, OUTPUT);
  pinMode(directionB1, OUTPUT);

  //Standby mode of the car
  digitalWrite(directionA1,LOW);
  digitalWrite(directionA2,LOW);
  digitalWrite(directionB1,LOW);
  digitalWrite(directionB1,LOW);
}

void loop() 
{
  while(Bt.available()) // Read data from the master device
  {
    state=Bt.read();
    switch(state)
    {

      case 'F':  // "FORWARD"
      dirA1=false;
      dirA2=true;
      dirB1=false;
      dirB2=true;
      controlDirection();
      break;


      case 'B': // "BACKWARD"
      dirA1=true;
      dirA2=false;
      dirB1=true;
      dirB2=false;
      controlDirection();
      break;


      case 'P':  //"PARK"
      dirA1=false;
      dirA2=false;
      dirB1=false;
      dirB2=false;
      controlDirection();
      break;

      case 'L':  //"STEER LEFT"
      dirA1=false;
      dirA2=false;
      dirB1=false;
      dirB2=true;
      controlDirection();
      break;

      case 'R':  //"STEER RIGHT"
      dirA1=false;
      dirA2=true;
      dirB1=false;
      dirB2=false;
      controlDirection();
      break;

      case 'I':  //"INCREASE THE SPEED"
      controlDirection();
      break;

      case 'D':  //"DECREASE THE SPEED"
      controlDirection();
      break;

      case 'M':  //"MAINTAIN THE SPEED"
      maintainSpeed =1;
      speedControl();
      break;



    }
  }
  
}

// Direction Control of the car
void controlDirection()
{
  digitalWrite(directionA1,dirA1);
  digitalWrite(directionA2,dirA2);
  digitalWrite(directionB1,dirB1);
  digitalWrite(directionB1,dirB2);
  speedControl();
}

// Speed control of the car
void speedControl()
{
  if(state=='I' ||  maintainSpeed == 1)
  {
    for(int i=motorSpeed; i<256; i++)
    {

      if( maintainSpeed == 1)
      {
        motorSpeed=i;
        maintainSpeed=0;
        break;
      }

      analogWrite(speedpinA,i);
      analogWrite(speedpinB,i);
      delay(20);
    }
  }
 

  if(state=='D' ||  maintainSpeed == 1)
  {
    for(int i=motorSpeed; i>0; i--)
    {

      if( maintainSpeed == 1)
      {
        motorSpeed=i;
        maintainSpeed=0;
        break;
      }


      analogWrite(speedpinA,i);
      analogWrite(speedpinB,i);
      delay(20);
    }
  }

  analogWrite(speedpinA,motorSpeed);
  analogWrite(speedpinB,motorSpeed);

}
