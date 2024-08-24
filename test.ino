#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <RTClib.h> // Library for DS3231 RTC

// Replace with your Wi-Fi credentials
const char* ssid = "rahulA15";
const char* password = "123456789";
// Replace with your Flask server's IP address and port
const char* serverName = "http://192.168.0.94:5007/receive_data";

// Create instances for sensors
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize I2C
  Wire.begin();

  // Initialize ADXL345 sensor
  if (!accel.begin()) {
    Serial.println("Couldn't find ADXL345");
    while (1);
  }
// Initialize DS3231 RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Uncomment this line if RTC time is not set, then comment it out after the time is set correctly
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) { // Check if we're still connected to the Wi-Fi network
    WiFiClient client;
    HTTPClient http;

    // Read acceleration data from ADXL345
    sensors_event_t event;
    accel.getEvent(&event);

    // Read date and time from DS3231
    DateTime now = rtc.now();

    // Read temperature from DS3231
    float temperature = rtc.getTemperature();

    // Format the datetime
    String datetime = String(now.year()) + "-" +
                      (now.month() < 10 ? "0" : "") + String(now.month()) + "-" +
                      (now.day() < 10 ? "0" : "") + String(now.day()) + "T" +
                      (now.hour() < 10 ? "0" : "") + String(now.hour()) + ":" +
                      (now.minute() < 10 ? "0" : "") + String(now.minute()) + ":" +
                      (now.second() < 10 ? "0" : "") + String(now.second());

    // Debugging line to print the datetime and temperature
    Serial.println("Current DateTime: " + datetime);
    Serial.println("Current Temperature: " + String(temperature) + " C");

    String data = "x=" + String(event.acceleration.x) +
                  "&y=" + String(event.acceleration.y) +
                  "&z=" + String(event.acceleration.z) +
                  "&datetime=" + datetime +
                  "&temperature=" + String(temperature);

    // Construct the server path with data query parameters
    String serverPath = String(serverName) + "?" + data;
// Pass the WiFiClient object and the URL to the begin method
    http.begin(client, serverPath);
    http.setTimeout(5000); // Set timeout to 5 seconds

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  }

  delay(10000); // Send data every 10 seconds
}
