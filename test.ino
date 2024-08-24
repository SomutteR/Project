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
