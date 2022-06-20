#include "DHTesp.h"
#include <WiFi.h>
#include <Wire.h>

String thingSpeakAddress = "api.thingspeak.com";
String writeAPIKey;
String tsfield1Name;
String request_string;
WiFiClient client;

const int DHT_PIN = 15;
DHTesp dhtSensor;

void dht() {

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  /*Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);*/

  int h = 0;
  float t =0;
  t = data.temperature, 2;
  h = data.humidity, 1;

  if (client.connect("api.thingspeak.com", 80)) {
    request_string = "/update?";
    request_string += "key=";
    request_string += "NB2ONMXKQ6IO0GVE";
    request_string += "&";
    request_string += "field1";
    request_string += "=";
    request_string += t;
    request_string += "&";
    request_string += "field2";
    request_string += "=";
    request_string += h;
    Serial.println(String("GET ") + request_string + " HTTP/1.1\r\n" +
                 "Host: " + thingSpeakAddress + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    client.print(String("GET ") + request_string + " HTTP/1.1\r\n" +
                 "Host: " + thingSpeakAddress + "\r\n" +
                 "Connection: close\r\n\r\n");
    

  } else {
      client.stop();
  Serial.println("stop");
  }
}

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  dht();
}