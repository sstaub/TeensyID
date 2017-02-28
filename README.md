# TeensyID
Teensy (USB-)Serialnumber, MAC-Address, Kinetis ChipUID and UUID (RFC4122)

Should work with Teensy LC & Teensy 3.0 ... 3.6

- Tested with Teensy 3.5 by sstaub
- Tested with teensy 3.2, WIZ850io, PRJC sd/Ethernet adapter, Arduino 1.8.11, TD 1.35, by bboyes

## Examples
### ReadAll
- just as it sounds, read and print out serial, mac, uid, uuid 
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

