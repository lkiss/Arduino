#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop()
{
  // while (Serial.available() > 0 && !Serial.readString().equals("WIFI_END"))
  // {
  //   String message = Serial.readString();
  //   Serial.println(message);
  // }

   // digitalWrite(9, LOW);
}