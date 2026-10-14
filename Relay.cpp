#include "header.h"

void relaySetup() {
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  // Active-low relay: HIGH = OFF
  digitalWrite(RELAY_LIGHT, HIGH);
  digitalWrite(RELAY_FAN, HIGH);
}

void setRelay(uint8_t relayPin, uint8_t value) {
  digitalWrite(relayPin, value);
}
