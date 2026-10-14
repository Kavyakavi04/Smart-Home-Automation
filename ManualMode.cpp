#include "header.h"

void handleManualControl(WiFiClient client) {

  client.setTimeout(1000);

  String request = client.readStringUntil('\r');
  client.readStringUntil('\n');

  Serial.println(request);


  // ==========================================
  // LIGHT MANUAL CONTROL
  // ==========================================

  if (request.indexOf("GET /?lightOn") >= 0) {

    lightManualMode = true;

    setRelay(RELAY_LIGHT, LOW);

    Serial.println("MANUAL: Light ON");
  }


  if (request.indexOf("GET /?lightOff") >= 0) {

    lightManualMode = true;

    setRelay(RELAY_LIGHT, HIGH);

    Serial.println("MANUAL: Light OFF");
  }


  // ==========================================
  // FAN MANUAL CONTROL
  // ==========================================

  if (request.indexOf("GET /?fanOn") >= 0) {

    fanManualMode = true;

    setRelay(RELAY_FAN, LOW);

    Serial.println("MANUAL: Fan ON");
  }


  if (request.indexOf("GET /?fanOff") >= 0) {

    fanManualMode = true;

    setRelay(RELAY_FAN, HIGH);

    Serial.println("MANUAL: Fan OFF");
  }


  // ==========================================
  // WEB PAGE
  // ==========================================

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html>");

  client.println("<head>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>ESP32 Home Automation</title>");
  client.println("</head>");

  client.println("<body>");

  client.println("<h1>ESP32 Home Automation</h1>");

  client.println("<h2>SMART MODE</h2>");

  client.println(
    "<p>Automatic and Manual control are available together.</p>"
  );


  // ==========================================
  // LIGHT
  // ==========================================

  client.println("<h3>Light</h3>");

  client.println(
    "<a href='/?lightOn'>"
    "<button>LIGHT ON</button>"
    "</a> "
  );

  client.println(
    "<a href='/?lightOff'>"
    "<button>LIGHT OFF</button>"
    "</a>"
  );


  // ==========================================
  // FAN
  // ==========================================

  client.println("<h3>Fan</h3>");

  client.println(
    "<a href='/?fanOn'>"
    "<button>FAN ON</button>"
    "</a> "
  );

  client.println(
    "<a href='/?fanOff'>"
    "<button>FAN OFF</button>"
    "</a>"
  );


  // ==========================================
  // CURRENT STATUS
  // ==========================================

  client.println("<hr>");

  client.println("<h2>Current Status</h2>");

  if (digitalRead(RELAY_LIGHT) == LOW) {
    client.println("<p>Light: ON</p>");
  } 
  else {
    client.println("<p>Light: OFF</p>");
  }

  if (digitalRead(RELAY_FAN) == LOW) {
    client.println("<p>Fan: ON</p>");
  } 
  else {
    client.println("<p>Fan: OFF</p>");
  }

  client.println("</body>");
  client.println("</html>");

  delay(1);

  client.stop();
}
