#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *host = "esp8266-webupdate";
const char *ssid = "PNSC";
const char *password = "5113111_Cons!";
const String deviceId = "Device01";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient http;

int ledPin = 2;
// int dht11Pin = 13;
// int waterLevelPin = 12;
// int waterPump01Pin = 5;
// int waterPump02Pin = 4;

String readFromSensorsAsJson()
{
  int soilMoistureValue = analogRead(A0);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    String error = "{\"errorCode\": \"READ_ERROR_DHT\"}";
    return error;
  }

  String jsonMessage = "[{\"reading\": ";
  jsonMessage += soilMoistureValue;
  jsonMessage += ", \"readingType\": SOIL_MOISTURE}, ";

  jsonMessage += "{\"reading\": ";
  jsonMessage += humidity;
  jsonMessage += ", \"readingType\": HUMIDITY}, ";

  jsonMessage += "{\"reading\": ";
  jsonMessage += temperature;
  jsonMessage += ", \"readingType\": TEMPERATURE}]";

  return jsonMessage;
}

void handleSensorRequest()
{
  httpServer.send(200, "application/json", readFromSensorsAsJson());
}

void postSensorReadings()
{
  http.addHeader("Content-Type", "application/json");
  http.POST(readFromSensorsAsJson());

  http.end();
}

void OTASetup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);

  httpUpdater.setup(&httpServer);

  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
}

void webServerSetup()
{
  httpServer.on("/sensor", handleSensorRequest);
}

void plantManagerServerSetup()
{
  http.begin("http://192.168.1.100:3000/sensor");
}

void dhtSensorSetup()
{
  dht.begin();
}

void setup(void)
{
  pinMode(ledPin, OUTPUT);
  OTASetup();
  webServerSetup();

  httpServer.begin();
}

void loop(void)
{
  httpServer.handleClient();
}