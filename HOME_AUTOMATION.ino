 #include "header.h"

// ==========================================
// WIFI SETTINGS
// ==========================================

const char* wifi_name = "ESPTEST";
const char* wifi_password = "12345678";

WiFiServer server(80);


// ==========================================
// WIFI SETUP + SCAN
// ==========================================

void wifiSetup() {

  Serial.println();
  Serial.println("==============================");
  Serial.println("STARTING WIFI");
  Serial.println("==============================");

  // Set ESP32 to Station mode
  WiFi.mode(WIFI_STA);

  // Disable Wi-Fi sleep for more reliable hotspot connection
  WiFi.setSleep(false);

  delay(500);


  // ==========================================
  // SCAN FOR WIFI NETWORKS
  // ==========================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("WIFI SCAN");
  Serial.println("==============================");

  // Clear previous scan results
  WiFi.scanDelete();

  int numberOfNetworks = WiFi.scanNetworks();

  if (numberOfNetworks < 0) {

    Serial.println("Wi-Fi scan failed.");

  }
  else if (numberOfNetworks == 0) {

    Serial.println("No Wi-Fi networks found.");

  }
  else {

    Serial.print(numberOfNetworks);
    Serial.println(" Wi-Fi networks found.");

    for (int i = 0; i < numberOfNetworks; i++) {

      Serial.print(i + 1);
      Serial.print(": ");

      Serial.print(WiFi.SSID(i));

      Serial.print(" | RSSI: ");

      Serial.print(WiFi.RSSI(i));

      Serial.print(" dBm");

      Serial.print(" | Channel: ");

      Serial.println(WiFi.channel(i));
    }
  }

  // Delete scan results to free memory
  WiFi.scanDelete();


  // ==========================================
  // CHECK WHETHER REDMI WAS FOUND
  // ==========================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("CHECKING WIFI NETWORK");
  Serial.println("==============================");

  Serial.print("Looking for: ");
  Serial.println(wifi_name);

  bool networkFound = false;

  int secondScan = WiFi.scanNetworks();

  if (secondScan > 0) {

    for (int i = 0; i < secondScan; i++) {

      if (WiFi.SSID(i) == String(wifi_name)) {

        networkFound = true;

        Serial.println("Target Wi-Fi found!");

        Serial.print("SSID: ");
        Serial.println(WiFi.SSID(i));

        Serial.print("RSSI: ");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm");

        Serial.print("Channel: ");
        Serial.println(WiFi.channel(i));

        break;
      }
    }
  }

  WiFi.scanDelete();


  if (!networkFound) {

    Serial.println();
    Serial.println("WARNING:");
    Serial.println("Target Wi-Fi was NOT found.");
    Serial.println("Check that the Redmi hotspot is ON.");
    Serial.println();

  }


  // ==========================================
  // CONNECT TO WIFI
  // ==========================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("CONNECTING TO WIFI");
  Serial.println("==============================");

  Serial.print("Wi-Fi Name: ");
  Serial.println(wifi_name);

  Serial.print("Password length: ");
  Serial.println(strlen(wifi_password));

  Serial.println("Starting connection...");


  // Make sure previous connection is cleared
  WiFi.disconnect(false);
  delay(500);

  // Start connection
  WiFi.begin(wifi_name, wifi_password);


  // ==========================================
  // WAIT FOR CONNECTION
  // ==========================================

  int count = 0;

  while (WiFi.status() != WL_CONNECTED && count < 60) {

    delay(500);

    Serial.print(".");

    count++;

    // Print status every 5 seconds
    if (count % 10 == 0) {

      Serial.print(" Status = ");
      Serial.println(WiFi.status());
    }
  }

  Serial.println();


  // ==========================================
  // CONNECTION SUCCESS
  // ==========================================

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.println("==============================");
    Serial.println("WIFI CONNECTED");
    Serial.println("==============================");

    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());

    Serial.print("Subnet: ");
    Serial.println(WiFi.subnetMask());

    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

    // Start web server
    server.begin();

    Serial.println();
    Serial.println("Web server started.");

    Serial.print("Open this address in your phone: ");
    Serial.println(WiFi.localIP());

    Serial.println();
    Serial.println("==============================");
    Serial.println("WIFI SETUP COMPLETE");
    Serial.println("==============================");
  }


  // ==========================================
  // CONNECTION FAILED
  // ==========================================

  else {

    Serial.println();
    Serial.println("==============================");
    Serial.println("WIFI CONNECTION FAILED");
    Serial.println("==============================");

    Serial.print("Final Wi-Fi status: ");
    Serial.println(WiFi.status());

    Serial.println();

    Serial.println("Possible causes:");

    Serial.println("1. Hotspot is OFF");
    Serial.println("2. Wi-Fi name is incorrect");
    Serial.println("3. Password is incorrect");
    Serial.println("4. Hotspot is using 5 GHz");
    Serial.println("5. Hotspot security is WPA3 only");
    Serial.println("6. ESP32 cannot authenticate with hotspot");
    Serial.println("7. Phone hotspot has reached its device limit");

    Serial.println();

    Serial.println("Recommended Redmi settings:");

    Serial.println("- Hotspot: ON");
    Serial.println("- AP Band: 2.4 GHz");
    Serial.println("- Security: WPA2");
    Serial.println("- SSID: Redmi");
    Serial.println("- Password: 12345678");

    Serial.println();
    Serial.print("Wi-Fi status code: ");
    Serial.println(WiFi.status());

    Serial.println("==============================");
  }
}


// ==========================================
// SETUP
// ==========================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 HOME AUTOMATION");
  Serial.println("==============================");


  // ==========================================
  // SENSOR AND RELAY SETUP
  // ==========================================

  Serial.println();
  Serial.println("Initializing devices...");

  relaySetup();

  DHTsetup();

  LDRsetup();

  ultraSonicSensorsetup();

  Serial.println("Devices initialized.");


  // ==========================================
  // WIFI SETUP
  // ==========================================

  wifiSetup();


  // ==========================================
  // SYSTEM STARTED
  // ==========================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("SYSTEM STARTED");
  Serial.println("==============================");
}


// ==========================================
// LOOP
// ==========================================

void loop() {


  // ==========================================
  // CHECK PHONE / BROWSER CONNECTION
  // ==========================================

  WiFiClient client = server.available();

  if (client) {

    handleManualControl(client);
  }


  // ==========================================
  // AUTOMATIC MODE
  // ==========================================

  handleAutoMode();


  // ==========================================
  // DHT11 READING INTERVAL
  // ==========================================

  delay(2000);
}
