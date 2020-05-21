# TeensyID
- Teensy (USB-)Serialnumber, MAC-Address, 
- Kinetis ChipUID and UUID (RFC4122) for Teensy 3.x and LC
- 64-bit UID for Teensy 4.x

Tested:
- Teensy 3.5 by sstaub
- Teensy 3.2, WIZ850io, PRJC sd/Ethernet adapter, Arduino 1.8.11, TD 1.35, by bboyes
- Teensy 3.6 amd LC by manitou
- Teensy 4.x by sstaub

## Examples
### **ReadAll** for Teensy 3.x and LC
```
#include "Arduino.h"
#include <TeensyID.h>

uint8_t serial[4];
uint8_t mac[6];
uint32_t uid[4];
uint8_t uuid[16];

void setup() {
  teensySN(serial);
  teensyMAC(mac);
  kinetisUID(uid);
  teensyUUID(uuid);
  delay(2000);
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());
  Serial.printf("Array Serialnumber: %02X-%02X-%02X-%02X \n", serial[0], serial[1], serial[2], serial[3]);
  Serial.printf("String Serialnumber: %s\n", teensySN());
  Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.printf("String MAC Address: %s\n", teensyMAC());
  Serial.printf("Array 128-bit UniqueID from chip: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);
  Serial.printf("String 128-bit UniqueID from chip: %s\n", kinetisUID());
  Serial.printf("Array 128-bit UUID RFC4122: %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n", uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
  Serial.printf("String 128-bit UUID RFC4122: %s\n", teensyUUID());
  }

void loop() {}
```

- Just as it sounds, read and print out serial, mac, uid, uuid 
- Typical output:
```
USB Serialnumber: 1244570 
Array Serialnumber: 00-01-E6-29 
String Serialnumber: 00-01-e6-29
Array MAC Address: 04:E9:E5:01:E6:29 
String MAC Address: 04:e9:e5:01:e6:29
Array 128-bit UniqueID from chip: C7210000-714D001E-00496017-31384E45
String 128-bit UniqueID from chip: c7210000-714d001e-00496017-31384e45
Array 128-bit UUID RFC4122: 00496017-3138-404E-8045-04E9E501E629
String 128-bit UUID RFC4122: 00496017-3138-404e-8045-04e9e501e629
```

### **T4_ReadAll** for Teensy 4.x
```
#include "Arduino.h"
#include <TeensyID.h>

uint8_t serial[4];
uint8_t mac[6];
uint8_t uid64[8];

void setup() {
  Serial.begin(9600);
  delay(2000);
  teensySN(serial);
  teensyMAC(mac);
  teensyUID64(uid64);
  Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());
  Serial.printf("Array Serialnumber: %02X-%02X-%02X-%02X \n", serial[0], serial[1], serial[2], serial[3]);
  Serial.printf("String Serialnumber: %s\n", teensySN());
  Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.printf("String MAC Address: %s\n", teensyMAC());
  Serial.printf("UID 64-bit: %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X\n", uid64[0], uid64[1], uid64[2], uid64[3], uid64[4], uid64[5], uid64[6], uid64[7]);
  Serial.printf("UID 64-bit: %s\n", teensyUID64());
  }

void loop() {}
```