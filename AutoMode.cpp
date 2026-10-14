#include "header.h"

// Manual override status
bool lightManualMode = false;
bool fanManualMode = false;

void handleAutoMode() {

  float distance = getDistance();
  float temperature = getTemp();
  bool roomIsLight = isItLight();

  bool humanPresent =
      (distance > 0 && distance <= HUMAN_DISTANCE_CM);

  // ==========================================
  // LIGHT AUTOMATIC CONTROL
  // ==========================================

  if (!lightManualMode) {

    if (!humanPresent) {

      setRelay(RELAY_LIGHT, HIGH);
      Serial.println("AUTO: No person -> Light OFF");

    }
    else if (!roomIsLight) {

      setRelay(RELAY_LIGHT, LOW);
      Serial.println("AUTO: Person + Dark -> Light ON");

    }
    else {

      setRelay(RELAY_LIGHT, HIGH);
      Serial.println("AUTO: Person + Bright -> Light OFF");
    }

  }
  else {

    Serial.println("MANUAL MODE: Light control active");
  }


  // ==========================================
  // FAN AUTOMATIC CONTROL
  // ==========================================

  if (!fanManualMode) {

    if (!humanPresent) {

      setRelay(RELAY_FAN, HIGH);
      Serial.println("AUTO: No person -> Fan OFF");

    }
    else if (temperature >= FAN_TEMP_C) {

      setRelay(RELAY_FAN, LOW);
      Serial.println("AUTO: High temperature -> Fan ON");

    }
    else {

      setRelay(RELAY_FAN, HIGH);
      Serial.println("AUTO: Normal temperature -> Fan OFF");
    }

  }
  else {

    Serial.println("MANUAL MODE: Fan control active");
  }
}
