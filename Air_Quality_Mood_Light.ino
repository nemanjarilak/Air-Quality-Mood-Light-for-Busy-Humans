#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// ========== WIFI & API CONFIGURATION ========== //
const char* ssid = "SSID";          // Your WiFi network name
const char* password = "PASS";   // WiFi password (maybe not your birthyear?)
const String API_KEY = "API KEY";  // AirVisual API key
const float LATITUDE = 40.000000;    // Your location's latitude
const float LONGITUDE = 20.000000;   // Your location's longitude

// ========== LED PIN CONFIGURATION ========== //
#define RED_PIN D5    // Red LED control
#define GREEN_PIN D6  // Green LED control
#define BLUE_PIN D7   // Blue LED control

// ========== COLOR MANAGEMENT STRUCTURE ========== //
struct Color {
  int r;         // Red intensity (0-255)
  int g;         // Green intensity (0-255)
  int b;         // Blue intensity (0-255)
  bool blink;    // Breathing effect toggle
};

// Function prototypes
void setColor(Color newColor);       // Set target color for LED
void fetchAQIData();                 // Get air quality from API
void updateLED();                    // Handle color transitions/effects
Color getColorForAQI(int aqi);       // Convert AQI to color scheme

Color targetColor = {0, 0, 0, false};  // Desired end color
Color currentColor = {0, 0, 0, false}; // Current displayed color
unsigned long lastUpdate = 0;          // Last API update timestamp

void setup() {
  Serial.begin(115200);
  
  // Initialize LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to: " + String(ssid));
  
  // Set PWM range and initial color (calm blue)
  analogWriteRange(255);
  setColor({0, 0, 255, false});

  // Initial API call and timer setup
  fetchAQIData();
  lastUpdate = millis();
}

void loop() {
  // Handle WiFi connection drops
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    delay(5000);
    return;
  }

  // Update air quality every 30 minutes
  if (millis() - lastUpdate >= 1800000) {
    fetchAQIData();
    lastUpdate = millis();
  }

  // Continuously update LED effects
  updateLED();
}

// ========== AIR QUALITY DATA FETCHING ========== //
void fetchAQIData() {
  WiFiClient client;
  HTTPClient http;
  
  // Build API request URL
  String url = "http://api.airvisual.com/v2/nearest_city?lat=" + 
              String(LATITUDE, 6) + "&lon=" + String(LONGITUDE, 6) + 
              "&key=" + API_KEY;

  http.begin(client, url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    // Parse JSON response
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    // Extract AQI value and update LED
    int aqi = doc["data"]["current"]["pollution"]["aqius"];
    Serial.print("AQI: ");
    Serial.println(aqi);
    setColor(getColorForAQI(aqi));
  } else {
    // Red alert for API failures
    Serial.println("API Error: " + String(httpCode));
    setColor({255, 0, 0, true});
  }
  http.end();
}

// ========== AQI TO COLOR MAPPING ========== //
Color getColorForAQI(int aqi) {
  // EPA Air Quality Index color standards
  if (aqi <= 50) return {0, 255, 0, false};    // Good - Solid green
  if (aqi <= 100) return {0, 255, 0, true};    // Moderate - Breathing green
  if (aqi <= 150) return {0, 0, 255, false};   // Unhealthy sensitive - Solid blue
  if (aqi <= 200) return {0, 0, 255, true};    // Unhealthy - Breathing blue
  if (aqi <= 300) return {255, 0, 0, false};   // Very unhealthy - Solid red
  return {255, 0, 0, true};                    // Hazardous - Panic-red breathing
}

// ========== COLOR TRANSITION MANAGEMENT ========== //
void setColor(Color newColor) {
  targetColor = newColor;
}

void updateLED() {
  static unsigned long lastFade = 0;         // Last fade update time
  static unsigned long breathingStart = 0;   // Breathing effect timer
  const int FADE_INTERVAL = 30;              // Fade step duration (ms)
  const unsigned long BREATHING_PERIOD = 2000; // Breathing cycle duration

  if (targetColor.blink) {
    // Breathing effect: smooth intensity pulsation
    unsigned long now = millis();
    if (breathingStart == 0) breathingStart = now;
    
    // Calculate breathing phase (0-2 seconds cycle)
    float phase = fmod((now - breathingStart) / 1000.0, 2.0);
    float breathingFactor = (phase < 1.0) ? phase : 2.0 - phase;

    // Apply intensity modulation
    currentColor.r = targetColor.r * breathingFactor;
    currentColor.g = targetColor.g * breathingFactor;
    currentColor.b = targetColor.b * breathingFactor;

    // Update LED outputs
    analogWrite(RED_PIN, currentColor.r);
    analogWrite(GREEN_PIN, currentColor.g);
    analogWrite(BLUE_PIN, currentColor.b);
  } else {
    // Smooth color transition between current and target
    if (millis() - lastFade < FADE_INTERVAL) return;
    lastFade = millis();
    breathingStart = 0; // Reset breathing timer

    // Incrementally adjust each color channel
    currentColor.r += (targetColor.r > currentColor.r) ? 1 : -1;
    currentColor.g += (targetColor.g > currentColor.g) ? 1 : -1;
    currentColor.b += (targetColor.b > currentColor.b) ? 1 : -1;

    // Update LED outputs
    analogWrite(RED_PIN, currentColor.r);
    analogWrite(GREEN_PIN, currentColor.g);
    analogWrite(BLUE_PIN, currentColor.b);
  }
}
