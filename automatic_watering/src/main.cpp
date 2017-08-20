#include "Arduino.h"

int waterPumpPin = 12;
int moistureSensorPin = 19;
int waterLevelSensorPin = 18;
int waterTankFilledLedPin = 5;
int waterTankEmptyLedPin = 6;

int maxMoistureValue = 400;  //plant is wet
int minMoistureValue = 1000; //plant is dry
int optimalMoistureValue = 700;

int maxWaterValue = 615; //water tank is at maximum
int minWaterValue = 50;  //water tank is empty

int currentMoistureValue = 0;
int currentWaterValue = 0;

int wateringTime = 1000;
unsigned long waitTimeAfterWatering = 600000;

void setup()
{
    pinMode(waterPumpPin, OUTPUT);
    pinMode(moistureSensorPin, INPUT_PULLUP);
    pinMode(waterLevelSensorPin, INPUT_PULLUP);
    pinMode(waterTankFilledLedPin, OUTPUT);
    pinMode(waterTankEmptyLedPin, OUTPUT);

    Serial.begin(9600);

    currentMoistureValue = analogRead(moistureSensorPin);
    currentWaterValue = analogRead(waterLevelSensorPin);

    digitalWrite(waterPumpPin, HIGH);

    Serial.println("Moisture level: ");
    Serial.println(currentMoistureValue);

    Serial.println("Water level: ");
    Serial.println(currentWaterValue);
}

void loop()
{
    currentMoistureValue = analogRead(moistureSensorPin);
    currentWaterValue = analogRead(waterLevelSensorPin);
    if (currentWaterValue > minWaterValue)
    {
        digitalWrite(waterTankEmptyLedPin, LOW);
        if (currentMoistureValue > optimalMoistureValue)
        {
            Serial.println("Watering... ");
            digitalWrite(waterPumpPin, LOW);
            delay(wateringTime);
            digitalWrite(waterPumpPin, HIGH);
            delay(waitTimeAfterWatering);

            Serial.println("Reading values...");
            currentMoistureValue = analogRead(moistureSensorPin);
            currentWaterValue = analogRead(waterLevelSensorPin);

            Serial.println("Moisture level: ");
            Serial.println(currentMoistureValue);

            Serial.println("Water level: ");
            Serial.println(currentWaterValue);
        }
    }
    else
    {
        digitalWrite(waterTankFilledLedPin, LOW);
        digitalWrite(waterTankEmptyLedPin, HIGH);
    }

    if (currentWaterValue >= maxWaterValue)
    {
        digitalWrite(waterTankFilledLedPin, HIGH);
    }
}