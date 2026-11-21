// ---------------- BLYNK CONFIG ----------------
#define BLYNK_TEMPLATE_ID "TMPL3Y6XIsETp"
#define BLYNK_TEMPLATE_NAME "Temp Alert"
#define BLYNK_AUTH_TOKEN "y4tD_66WjJygXWxxDGml4yibP7qafkVm"

#define BLYNK_PRINT Serial  // Enable Blynk debug info

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// ---------------- WiFi & Blynk ----------------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ABC";    // WiFi SSID
char pass[] = "12345678";  // WiFi password

// ---------------- PINS ----------------
#define DHTPIN 14      // DHT22 data pin
#define BUZZER_PIN 26  // Passive buzzer pin

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------------- THRESHOLDS ----------------
#define TEMP_THRESHOLD 40.0  // Celsius

// ---------------- TIMER ----------------
BlynkTimer timer;

// ---------------- VARIABLES ----------------
bool buzzerEnabled = true;  // controlled from Blynk Switch (V3)
bool buzzerOn = false;
unsigned long buzzerStart = 0;
const unsigned long buzzerDuration = 1000; // 1 second beep

// ---------------- BUZZER CONTROL ----------------
void startBuzzer() {
  if (buzzerEnabled) {
    tone(BUZZER_PIN, 1000);
    buzzerOn = true;
    buzzerStart = millis();
  }
}

void stopBuzzer() {
  noTone(BUZZER_PIN);
  buzzerOn = false;
}

// ---------------- READ TEMPERATURE ----------------
void checkTemperature() {
  float temp = dht.readTemperature();  // Celsius

  if (isnan(temp)) {
    Serial.println("⚠️ Failed to read temperature!");
    return;
  }

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Send temperature to Blynk Label (V1)
  Blynk.virtualWrite(V1, temp);

  // Check threshold
  if (temp >= TEMP_THRESHOLD) {
    Serial.println("⚠️ Temperature threshold exceeded!");
    Blynk.logEvent("temp_alert", "High Temperature Detected!");
    Blynk.virtualWrite(V2, 255);  // Turn ON LED widget

    if (!buzzerOn && buzzerEnabled) startBuzzer(); // Start buzzer non-blocking
  } else {
    Blynk.virtualWrite(V2, 0);   // Turn OFF LED widget
    stopBuzzer();
  }

  // Stop buzzer automatically after 1 sec
  if (buzzerOn && (millis() - buzzerStart >= buzzerDuration)) {
    stopBuzzer();
  }
}

// ---------------- BLYNK: SWITCH CONTROL ----------------
BLYNK_WRITE(V3) {  // Blynk Switch on V3
  int value = param.asInt();
  if (value == 1) {
    buzzerEnabled = true;
    Serial.println("🔔 Buzzer ENABLED remotely");
  } else {
    buzzerEnabled = false;
    stopBuzzer();
    Serial.println("🔕 Buzzer DISABLED remotely");
  }
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n--- DHT22 Temperature Alert System ---");

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  dht.begin();

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
    Blynk.config(auth);
    if (Blynk.connect()) {
      Serial.println("✅ Connected to Blynk Cloud!");
    } else {
      Serial.println("⚠️ Blynk not connected!");
    }
  } else {
    Serial.println("\n⚠️ WiFi not connected. Running offline mode.");
  }

  timer.setInterval(3000L, checkTemperature);  // Read every 3 seconds
}

// ---------------- LOOP ----------------
void loop() {
  Blynk.run();
  timer.run();
}
