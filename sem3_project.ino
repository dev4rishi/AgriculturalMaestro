#include <EEPROM.h>

int soil_pin1=A1, soil_pin2=A2, soil_val1=0, soil_val2=0, address=0;

void setup() 
{
  pinMode(soil_pin1,INPUT); 
  pinMode(soil_pin2,INPUT); 
  //Serial.begin(9600);
}

void loop() 
{
  soil_val1= analogRead(soil_pin1);
  soil_val2= analogRead(soil_pin2);
  int val=(soil_val1+soil_val2)/2;
  val=map(val,595,239,0,100);
  EEPROM.update(address, val);
  address = address + 1;
  if (address == EEPROM.length()) 
  {
    delay(3600000);
    address = 0;
  }
  delay(84000);/*
  Serial.print(soil_val1);
  Serial.print("  ");
  Serial.print(soil_val2);
  Serial.print("  ");
  Serial.println(val);
  //delay(1000);*/
}
