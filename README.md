Check and return temperature by digital sensor DS1820 connected by 1-Wire line. If you use more than one sensor you need to use the OneWire and the DallasTemperature libraries.
   Arduino                  DS18B20 #1      DS18B20 #2      DS18B20 #3
   ┌──────┐                 ┌────────┐      ┌────────┐      ┌────────┐
   │      │                 │        │      │        │      │        │
   │  5V ─┼────┬────────────┤ VDD    ├──────┤ VDD    ├──────┤ VDD    │
   │      │    │            │        │      │        │      │        │
   │ GND ─┼────┼────────────┤ GND    ├──────┤ GND    ├──────┤ GND    │
   │      │    │            │        │      │        │      │        │
   │ D2  ─┼────┼────[4.7k]──┤ DQ     ├──────┤ DQ     ├──────┤ DQ     │
   │      │    │            └────────┘      └────────┘      └────────┘
   └──────┘    │
               └── резистор подтяжки к +5V (один на всю шину)

      ┌─────┐
      │ 1 2 3│
      └──┴─┴─┘
       │  │  │
      GND DQ VDD
