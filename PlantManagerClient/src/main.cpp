#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>
#include <ArduinoJson.h>

int pinDHT11 = 14;
int pinSoilMoisture01 = 4;
int pinSoilMoisture02 = 5;
SimpleDHT11 dht11;

const char *host = "esp8266-webupdate";
const char *ssid = "PNSC";
const char *password = "5113111_Cons!";
const String deviceId = "Device01";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient http;
DynamicJsonBuffer jsonBuffer(200);

int readFromSoilMoistureSensor(int poweringPin)
{
  int result = 0;
  digitalWrite(poweringPin, HIGH);
  delay(50);
  result = analogRead(A0);
  digitalWrite(poweringPin, LOW);
  delay(50);
  return result;
}

int *readFromDHT11Sensor(int *results)
{
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    results[0] = -1;
    results[1] = -1;
    return results;
  }

  results[0] = (int)temperature;
  results[1] = (int)humidity;
  return results;
}

String readFromSensorsAsJson()
{
  String jsonMessage;

  int *dht11Value = new int[2];
  int soilMoistureValue01 = readFromSoilMoistureSensor(pinSoilMoisture01);
  int soilMoistureValue02 = readFromSoilMoistureSensor(pinSoilMoisture02);
  dht11Value = readFromDHT11Sensor(dht11Value);

  JsonArray &jsonArray = jsonBuffer.createArray();

  JsonObject &soilMoistureReading01 = jsonBuffer.createObject();
  soilMoistureReading01["sensor"] = "SOIL_MOISTURE";
  soilMoistureReading01["value"] = soilMoistureValue01;
  soilMoistureReading01["sensorIndex"] = 1;
  soilMoistureReading01["unit"] = "%";
  jsonArray.add(soilMoistureReading01);

  JsonObject &soildMoistureReading02 = jsonBuffer.createObject();
  soildMoistureReading02["sensor"] = "SOIL_MOISTURE";
  soildMoistureReading02["value"] = soilMoistureValue02;
  soildMoistureReading02["sensorIndex"] = 2;
  soildMoistureReading02["unit"] = "%";
  jsonArray.add(soildMoistureReading02);

  JsonObject &temperatureReading01 = jsonBuffer.createObject();
  temperatureReading01["sensor"] = "TEMPERATURE";
  temperatureReading01["value"] = dht11Value[0];
  temperatureReading01["sensorIndex"] = 1;
  temperatureReading01["unit"] = "C";
  jsonArray.add(temperatureReading01);

  JsonObject &humidityReading01 = jsonBuffer.createObject();
  humidityReading01["sensor"] = "HUMIDITY";
  humidityReading01["value"] = dht11Value[1];
  humidityReading01["sensorIndex"] = 1;
  humidityReading01["unit"] = "%";
  jsonArray.add(humidityReading01);

  jsonArray.printTo(jsonMessage);
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
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
  }

  MDNS.begin(host);

  httpUpdater.setup(&httpServer);

  MDNS.addService("http", "tcp", 80);
}

void webServerSetup()
{
  httpServer.on("/sensor", handleSensorRequest);
}

void plantManagerServerSetup()
{
  http.begin("http://192.168.1.100:3000/sensor");
}

void soilMoistureSetup()
{
  pinMode(pinSoilMoisture01, OUTPUT);
  pinMode(pinSoilMoisture02, OUTPUT);

  digitalWrite(pinSoilMoisture01, LOW);
  digitalWrite(pinSoilMoisture02, LOW);
}

void setup(void)
{
  OTASetup();
  webServerSetup();
  soilMoistureSetup();

  httpServer.begin();
}

void loop(void)
{
  httpServer.handleClient();
}