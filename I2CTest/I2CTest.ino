#include <Wire.h>

#define SLAVE_ADDR 0x74 // Slave device address
#define REG_ADDR   0x00 // Example register address
#define DATA       0xAB // Example data to be sent

void setup() {
  Wire1.begin(1, 2); // Wire1 on pins IO8 (SDA) and IO9 (SCL)
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Initializing I2C communication...");
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(REG_ADDR); // Send register address
  Wire.write(DATA);     // Send data to the register
  Wire.endTransmission();
  
  Serial.println("Data sent to the slave device.");
}

void loop() {
  // Nothing to do here
  delay(1000);
  
  Serial.println("Initializing I2C communication...");
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(REG_ADDR); // Send register address
  Wire.write(DATA);     // Send data to the register
  Wire.endTransmission();
  
  Serial.println("Data sent to the slave device.");
}
