#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <RTClib.h> 
const char* ssid = "rahulA15";
const char* password = "123456789";
const char* serverName = "http://192.168.0.94:5007/receive_data";
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
RTC_DS3231 rtc;
void setup() {
  Serial.begin(115200);
  delay(10);
  Wire.begin();
  if (!accel.begin()) {
    Serial.println("Couldn't find ADXL345");
    while (1);
  }
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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
  if (WiFi.status() == WL_CONNECTED) { 
    WiFiClient client;
    HTTPClient http;
    sensors_event_t event;
    accel.getEvent(&event);
    DateTime now = rtc.now();
    float temperature = rtc.getTemperature();
    String datetime = String(now.year()) + "-" +
                      (now.month() < 10 ? "0" : "") + String(now.month()) + "-" +
                      (now.day() < 10 ? "0" : "") + String(now.day()) + "T" +
                      (now.hour() < 10 ? "0" : "") + String(now.hour()) + ":" +
                      (now.minute() < 10 ? "0" : "") + String(now.minute()) + ":" +
                      (now.second() < 10 ? "0" : "") + String(now.second());
    Serial.println("Current DateTime: " + datetime);
    Serial.println("Current Temperature: " + String(temperature) + " C");
    String data = "x=" + String(event.acceleration.x) +
                  "&y=" + String(event.acceleration.y) +
                  "&z=" + String(event.acceleration.z) +
                  "&datetime=" + datetime +
                  "&temperature=" + String(temperature);
    String serverPath = String(serverName) + "?" + data;
    http.begin(client, serverPath);
    http.setTimeout(5000); 
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(10000); 
}
