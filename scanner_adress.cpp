#include <OneWire.h>

OneWire ds(2);

void setup() {
  Serial.begin(9600);
  Serial.println("Сканер 1-Wire устройств");
}

void loop() {
  byte addr[8];

  if (!ds.search(addr)) {
    Serial.println("Нет устройств.");
    ds.reset_search();
    delay(2000);
    return;
  }

  Serial.print("Адрес: ");
  for (int i = 0; i < 8; i++) {
    if (addr[i] < 16) Serial.print("0");
    Serial.print(addr[i], HEX);
    if (i < 7) Serial.print(", ");
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println(" [неверный CRC]");
    return;
  }

  if (addr[0] == 0x28)      Serial.println(" -> DS18B20");
  else if (addr[0] == 0x10) Serial.println(" -> DS18S20");
  else                       Serial.println(" -> неизвестное устройство");

  delay(100);
}