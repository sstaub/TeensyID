# TeensyID
Teensy (USB-)Serialnumber, Kinetis ChipUID, and MAC-Address

Based on the TeensMAC library from Frank Boesing

Should work with Teensy LC & Teensy 3.0 .. 3.6

The new library was only tested with Teensy 3.5

Example:

```
#include <TeensyID.h>

uint8_t mac[6];
uint8_t uid[4];
uint8_t serial[4];

void setup() {
  teensyMAC(mac);
  kinetisUID(uid);
  teensySN(serial);
  delay(2000);
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());
  Serial.printf("Array Serialnumber: %02X-%02X-%02X-%02X \n", serial[0], serial[1], serial[2], serial[3]);
  Serial.printf("String Serialnumber: %s\n", teensySN());
  Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.printf("String MAC Address: %s\n", teensyMAC());
  Serial.printf("Array 128-bit UniqueID from chip: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);
  Serial.printf("String 128-bit UniqueID from chip: %s\n", kinetisUID());
}

void loop() {}
```
