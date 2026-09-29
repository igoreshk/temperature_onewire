//Код реализует BLE-маяк (beacon), который транслирует температуру через рекламные пакеты Bluetooth Low Energy.

#include <OneWire.h>
#include "SimpleBLE.h"

#define ONE_WIRE_PIN      2
#define REC_THRESHOLD     5
#define CONVERSION_MS     750

OneWire ds(ONE_WIRE_PIN);
SimpleBLE ble;

String beaconMsg = "ESP00";
int rec = 0;
uint32_t lastMs = 0;

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    ble.begin(beaconMsg);      // один раз
    lastMs = millis();
}

void loop() {
    if (millis() - lastMs < 1000) return;
    lastMs = millis();

    float temperature = getTemp();
    int t100 = isnan(temperature) ? -100000 : (int)(temperature * 100);

    if (isnan(temperature)) {
        rec++;
        if (rec > REC_THRESHOLD) {
            beaconMsg = "ESPSNA";
        }
    } else {
        rec = 0;
        char buf[16];
        snprintf(buf, sizeof(buf), "ESP%d", t100);
        beaconMsg = buf;
    }

    Serial.printf("t=%.2f rec=%d msg=%s\n", temperature, rec, beaconMsg.c_str());

    // В SimpleBLE нет update — приходится перезапускать
    ble.end();
    ble.begin(beaconMsg);
}

float getTemp() {
    byte data[9];
    byte addr[8];

    if (!ds.search(addr)) {
        ds.reset_search();
        Serial.println("no addr found");
        return NAN;
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC invalid");
        return NAN;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28) {
        Serial.println("Device not recognized");
        return NAN;
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);
    delay(CONVERSION_MS);        // ждём преобразование
    ds.reset();
    ds.select(addr);
    ds.write(0xBE);

    for (int i = 0; i < 9; i++) data[i] = ds.read();

    int16_t raw = (int16_t)((data[1] << 8) | data[0]);

    // DS18B20: /16 ; DS18S20: /2
    if (addr[0] == 0x10) {
        return raw / 2.0f;
    }
    return raw / 16.0f;
}