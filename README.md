Check and return temperature by digital sensor DS1820 connected by 1-Wire line. If you use more than one sensor you need to use the OneWire and the DallasTemperature libraries.

         +5V ●──────────┬──────────────┬─────────────┐
                        │              │             │
                       [R]            VDD            │
                      4.7kΩ            │             │
                        │              │         ┌───┴───┐
   Arduino Pin 2 ●──────┴──────────────┼─────────┤  DQ   │
                                        │         │DS18B20│
   Arduino GND ●────────────────────────┴─────────┤  GND  │
                                                  └───────┘
