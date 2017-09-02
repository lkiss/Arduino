#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>
#include <ArduinoJson.h>
#include <Timer.h>
#include <Gsender.h>

int pinDHT11 = 14;
int pinSoilMoisture01 = 4;
int pinSoilMoisture02 = 5;
int pinWaterPump01 = 12;
int pinWaterPump02 = 13;
int pinWaterSensor = 16;

long wateringTime = 2000;
long timeBetweenWatering = 60000 * 30;
int soilMoistureDryValue = 850;
int soilMoistureWetValue = 600;
int soilMoistureMiddleValue = 725;

Timer timer;
SimpleDHT11 dht11;

const char *host = "esp8266-webupdate";
const char *ssid = "PNSC";
const char *password = "5113111_Cons!";

String smtpUser = "kisslac88@gmail.com";
String smtpPassword = "5113111_Cons";
String deviceId = "Device01";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient http;
DynamicJsonBuffer jsonBuffer(200);

void sendEmail(String subject, String emailTo, String body)
{
  Gsender *gsender = Gsender::Instance();
  if (gsender->Subject(subject)->Send(emailTo, body))
  {
    Serial.println("Message send.");
  }
  else
  {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}

int readFromSoilMoistureSensor(int poweringPin)
{
  //Log debug
  int result = 0;
  digitalWrite(poweringPin, HIGH);
  delay(50);
  result = analogRead(A0);
  digitalWrite(poweringPin, LOW);
  delay(50);
  return result;
}

bool isWateringNeeded(int soilMoisturePin)
{
  //Log debug
  int soilMoistureValue = readFromSoilMoistureSensor(soilMoisturePin);
  if (soilMoistureValue >= soilMoistureDryValue)
  {
    return true;
  }
  else if (soilMoistureValue >= soilMoistureMiddleValue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int *readFromDHT11Sensor(int *results)
{
  //Log debug
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

bool canActivateWaterPump()
{
  int isWateringAllowed = digitalRead(pinWaterSensor);

  if (isWateringAllowed == 1)
  {
    //Log debug
    return true;
  }
  else
  {
    sendEmail("Water tank empty!", "kisslac1988@hotmail.com", "Please refill water tank!");
    //Log warning
    return false;
  }
}

void activateWaterPump(int waterPumpPin)
{
  if (canActivateWaterPump())
  {
    //Log debug
    digitalWrite(waterPumpPin, LOW);
    delay(wateringTime);
    digitalWrite(waterPumpPin, HIGH);
  }
  else
  {
    //Log warning
  }
}

String getSensorReadingsAsJson()
{
  //Log debug
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
  httpServer.send(200, "application/json", getSensorReadingsAsJson());
}

void handleWaterPumpRequest()
{
  activateWaterPump(pinWaterPump01);
  activateWaterPump(pinWaterPump02);
  httpServer.send(200);
}

void water()
{
  //Log debug
  bool isWateringNeeded01 = isWateringNeeded(pinSoilMoisture01);
  bool isWateringNeeded02 = isWateringNeeded(pinSoilMoisture02);

  if (isWateringNeeded01 == true)
  {
    activateWaterPump(pinWaterPump01);
  }

  if (isWateringNeeded02 == true)
  {
    activateWaterPump(pinWaterPump02);
  }
}

void postSensorReadings()
{
  http.addHeader("Content-Type", "application/json");
  http.POST(getSensorReadingsAsJson());

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
  httpServer.on("/sensor/waterpump", handleWaterPumpRequest);
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

void waterPumpAndSensorSetup()
{
  pinMode(pinWaterPump01, OUTPUT);
  pinMode(pinWaterPump02, OUTPUT);
  pinMode(pinWaterSensor, INPUT);

  digitalWrite(pinWaterPump01, HIGH);
  digitalWrite(pinWaterPump02, HIGH);
}

void setup(void)
{
  OTASetup();
  webServerSetup();
  soilMoistureSetup();
  waterPumpAndSensorSetup();

  httpServer.begin();
  timer.every(timeBetweenWatering, water);
}

void loop(void)
{
  httpServer.handleClient();
  timer.update();
}