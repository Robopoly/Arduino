// use Arduino EEPROM functions
// reference: http://arduino.cc/en/Reference/EEPROM
#include <EEPROM.h>

#define LED PC(2)

int adress;
unsigned char value;
unsigned char i;

void setup()
{
  // these values will remain in EEPROM even if the device is reset
  // this means when this part has run once you can remove it
  for(i = 0; i < 5; i++)
  {
    adress = i;
    value = 4-i;
    // write the value to adress in EEPROM
    EEPROM.write(adress, value);
  }
  
  Serial.begin(9600);
  // reset adress counter
  adress = 0;
}

void loop()
{
  // read EEPROM value
  value = EEPROM.read(adress);
  
  // output to serial
  Serial.write("adress: ");
  Serial.print(adress);
  Serial.write(", value: ");
  Serial.println(value);
  
  // loop over the first 5 values in EEPROM
  adress++;
  if(adress == 5)
  {
     adress = 0;
  }
  
  delay(1000);
}
