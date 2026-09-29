#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Адреса конкретных датчиков (получить через сканер)
DeviceAddress sensor1 = { 0x28, 0xFF, 0x64, 0x1E, 0x0A, 0x00, 0x00, 0xAB };
DeviceAddress sensor2 = { 0x28, 0xFF, 0x12, 0x34, 0x56, 0x00, 0x00, 0xCD };

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printTemperature(DeviceAddress addr) {
  float tempC = sensors.getTempC(addr);
  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("Ошибка чтения!");
  } else {
    Serial.print(tempC);
    Serial.print(" °C");
  }
}

void setup() {
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(sensor1, 12);
  sensors.setResolution(sensor2, 12);
}

void loop() {
  sensors.requestTemperatures();

  Serial.print("Датчик 1: ");
  printTemperature(sensor1);
  Serial.println();

  Serial.print("Датчик 2: ");
  printTemperature(sensor2);
  Serial.println("\n---");

  delay(2000);
}