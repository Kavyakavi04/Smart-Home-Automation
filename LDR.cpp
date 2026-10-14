#include "header.h"

void LDRsetup() {
  pinMode(LDR_PIN, INPUT);
}

bool isItLight() {
  int ldrValue = digitalRead(LDR_PIN);

  Serial.print("LDR Digital Value: ");
  Serial.println(ldrValue);

  // Check according to your LDR module.
  if (ldrValue == LOW) {
    Serial.println("Room is dark");
    return true;
  } else {
    Serial.println("Room is bright");
    return false;
  }
}
