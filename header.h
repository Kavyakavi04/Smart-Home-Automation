#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>


// ==========================================
// ESP32 PIN CONNECTIONS
// ==========================================

#define DHT_PIN 4
#define LDR_PIN 21

#define TRIG_PIN 27
#define ECHO_PIN 26

#define RELAY_LIGHT 5
#define RELAY_FAN 15


// ==========================================
// SETTINGS
// ==========================================

// Maximum distance at which a person is detected
#define HUMAN_DISTANCE_CM 10.0

// Fan turns ON when temperature reaches this value
#define FAN_TEMP_C 20.0


// ==========================================
// DHT11 FUNCTIONS
// ==========================================

void DHTsetup();
float getTemp();


// ==========================================
// LDR FUNCTIONS
// ==========================================

void LDRsetup();
bool isItLight();


// ==========================================
// ULTRASONIC FUNCTIONS
// ==========================================

void ultraSonicSensorsetup();
float getDistance();


// ==========================================
// RELAY FUNCTIONS
// ==========================================

void relaySetup();

void setRelay(
  uint8_t relayPin,
  uint8_t value
);


// ==========================================
// WIFI FUNCTIONS
// ==========================================

void wifiSetup();


// ==========================================
// AUTOMATIC MODE
// ==========================================

void handleAutoMode();


// ==========================================
// MANUAL WEB CONTROL
// ==========================================

void handleManualControl(WiFiClient client);


// ==========================================
// MANUAL MODE VARIABLES
// ==========================================

// true  = device is under manual control
// false = device is controlled automatically

extern bool lightManualMode;
extern bool fanManualMode;


#endif
