#include "Arduino.h"

int stopButtonPin = 2;
int startButtonPin = 3;
int motionSensorPin = 4;

int motionStatusLedPin = 5;
int startStatusLedPin = 6;
int stopStatusLedPin = 7;

void setup()
{
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(motionSensorPin, INPUT_PULLUP);

  pinMode(motionStatusLedPin, OUTPUT);
  pinMode(startStatusLedPin, OUTPUT);
  pinMode(stopStatusLedPin, OUTPUT);

  digitalWrite(stopStatusLedPin, HIGH);

  Serial.begin(9600);
  delay(2000);
}

void loop()
{
  if (digitalRead(startButtonPin) == LOW)
  {
    Serial.println("Sensor started");
    digitalWrite(startStatusLedPin, HIGH);
    digitalWrite(stopStatusLedPin, LOW);

    while (digitalRead(stopButtonPin) == HIGH)
    {
      if(digitalRead(stopButtonPin) == LOW)
        Serial.println("Stop motion sensor");

      delay(100);
      if (digitalRead(motionSensorPin) == HIGH)
      {
        Serial.println("Motion detected!");
        digitalWrite(motionStatusLedPin, HIGH);
      }
      else
      {
        digitalWrite(motionStatusLedPin, LOW);
      }
    }
    Serial.println("Sensor stopped");
    digitalWrite(startStatusLedPin, LOW);
    digitalWrite(stopStatusLedPin, HIGH);
  }
}