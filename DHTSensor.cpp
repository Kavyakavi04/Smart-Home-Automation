#include "header.h"
#include <DHT.h>

#define DHT_TYPE DHT11

// Create DHT11 sensor object
DHT dht(DHT_PIN, DHT_TYPE);

// Initialize the DHT11 sensor
void DHTsetup() {
  dht.begin();
}

// Read and return room temperature in Celsius
float getTemp() {
  float temperature = dht.readTemperature();

  // Check whether the sensor reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT11.");
    return 0;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  return temperature;
}
