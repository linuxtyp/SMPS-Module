#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x74
#define SDA_PIN 21
#define SCL_PIN 22
#define BAUDRATE 100000

#define NUM_REGISTERS 10  // Anzahl der Register

byte registers[NUM_REGISTERS] = {0};  // Array, um Registerwerte zu speichern
byte registerAddress = 0;  // Aktuelle Registeradresse

void setup() {
  Wire1.begin(I2C_SLAVE_ADDRESS, SDA_PIN, SCL_PIN, BAUDRATE); // Initialisiere den I2C-Bus als Slave mit Adresse 0x74
  Wire1.onReceive(receiveEvent); // Setze die Callback-Funktion für Empfangsereignisse
  Wire1.onRequest(requestEvent); // Setze die Callback-Funktion für Anforderungsereignisse
  Serial.begin(115200); // Initialisiere die serielle Kommunikation zur Debugging-Ausgabe
  Serial.println("Setup complete");
}

void loop() {
  // Im Hauptprogramm wird nichts benötigt, die Ereignisfunktionen übernehmen die Arbeit
  delay(1000);
  Serial.println("Looping...");
}

// Diese Funktion wird aufgerufen, wenn Daten vom Master gesendet werden
void receiveEvent(int howMany) {
  if (howMany < 1) return;  // Keine Daten empfangen

  registerAddress = Wire1.read();  // Lese die Registeradresse
  Serial.print("Register-Adresse empfangen: 0x");
  Serial.println(registerAddress, HEX);

  byte i = 0;
  while (Wire1.available()) {
    registers[registerAddress + i] = Wire1.read();  // Lese die Registerwerte
    Serial.print("Wert geschrieben: Register[0x");
    Serial.print(registerAddress + i, HEX);
    Serial.print("] = 0x");
    Serial.print(registers[registerAddress + i], HEX);
    Serial.print(" (");
    Serial.print(registers[registerAddress + i], DEC);
    Serial.println(")");
    i++;
  }
}

// Diese Funktion wird aufgerufen, wenn der Master Daten vom Slave anfordert
void requestEvent() {
  Serial.print("Leseanforderung für Register[0x");
  Serial.print(registerAddress, HEX);
  Serial.println("]");

  Wire1.write(registers[registerAddress]);  // Sende den Registerwert an den Master
  Serial.print("Gesendet: 0x");
  Serial.print(registers[registerAddress], HEX);
  Serial.print(" (");
  Serial.print(registers[registerAddress], DEC);
  Serial.println(")");
}
