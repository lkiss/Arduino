#include <SimpleDHT.h>
#include "dht11Service.h"

SimpleDHT11 dht11;

DHT11Service::DHT11Service(int DHT11Pin){
  this->DHT11Pin = DHT11Pin;
}

int* DHT11Service::read(int *results)
{
  //Log debug
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(this->DHT11Pin, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    results[0] = -1;
    results[1] = -1;
    return results;
  }

  results[0] = (int)temperature;
  results[1] = (int)humidity;
  return results;
}