#include "DFRobot_DF2301Q.h"
#include <SoftwareSerial.h>

//I2C communication
DFRobot_DF2301Q_I2C asr; // activates the I2C mode of the voice recognition module
SoftwareSerial Bt(2, 3);  // RX, TX

void setup() 
{

  Serial.begin(38400);  
  Bt.begin(38400);
  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(7);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.println("wakeTime = ");
  Serial.println(wakeTime);

  asr.playByCMDID(1);   // Wake-up command

  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID
}

void loop() 
{
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  Serial.println(CMDID);
  switch (CMDID) 
  {
    // Custom commands in English

    case 5: // "FORWARD"
    Bt.write('F');
    break;
    
    case 6: // "BACKWARD"
    Bt.write('B');
    break;

    case 7: // "PARK"
    Bt.write('P');
    break;

    case 8: // "STEER LEFT"
    Bt.write('L');
    break;

    case 9: // "STEER RIGHT"
    Bt.write('R');
    break;

    case 10:  // "INCREASE THE SPEED"
    Bt.write('R');                               
    break;

    case 11:  // "DECREASE THE SPEED"
    Bt.write('S');                                  
    break;

    case 12: // "MAINTAIN THE SPEED"
    Bt.write('M');
    break;

           
    default:
    Serial.println("Invalid Command");
    break;
  }
  delay(300);
}