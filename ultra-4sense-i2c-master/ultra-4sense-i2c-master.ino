/*
  I2C Ultrasonic 4 Sensors Master
  ultra-4sense-i2c-master.ino
  Receives data from 4 remote Ultrasonic Sensors
  Uses I2C Interface

  DroneBot Workshop 2019
  http://dronebotworkshop.com
*/

// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define counter to count bytes in response
int bcount;

// Define array for return data
byte distance[4];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

byte readI2C(int address) {
  // Define a variable to hold byte of data
  byte bval ;
  long entry = millis();
  // Read one byte at a time
  Wire.requestFrom(address, 1);
  // Wait 100 ms for data to stabilize
  while (Wire.available() == 0 && (millis() - entry) < 100)  Serial.print("Waiting");
  // Place data into byte
  if  (millis() - entry < 100) bval = Wire.read();
  return bval;
}

void loop()
{

  while (readI2C(SLAVE_ADDR) < 255) {
    // Until first byte has been received print a waiting message
    Serial.print("Waiting");
  }
  for (bcount = 0; bcount < 4; bcount++) {
    distance[bcount] = readI2C(SLAVE_ADDR);
  }
  for (int i = 0; i < 4; i++) {
    Serial.print(distance[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(200);
}
