/* TeensyMAC library code is placed under the MIT license
 * Copyright (c) 2017 Stefan Staub
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/** Teensy Library for different IDs of Teensy LC and Teensy 3.0 ... 3.6
  *
  * - USB Serial Number
  * - Teensy Serial Number
  * - MAC Address
  * - Kinetis Chip UID
  * - UUID (RFC4122) pseudo v4
  *
  * @code
  *  #include <TeensyID.h>
  *
  * uint8_t serial[4];
  * uint8_t mac[6];
  * uint32_t uid[4];
  * uint8_t uuid[16];
  *
  * void setup() {
  *   teensySN(serial);
  *   teensyMAC(mac);
  *   kinetisUID(uid);
  *   teensyUUID(uuid);
  *   delay(2000);
  *   Serial.printf("USB Serialnumber: %u \n", teensyUsbSN());
  *   Serial.printf("Array Serialnumber: %02X-%02X-%02X-%02X \n", serial[0], serial[1], serial[2], serial[3]);
  *   Serial.printf("String Serialnumber: %s\n", teensySN());
  *   Serial.printf("Array MAC Address: %02X:%02X:%02X:%02X:%02X:%02X \n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  *   Serial.printf("String MAC Address: %s\n", teensyMAC());
  *   Serial.printf("Array 128-bit UniqueID from chip: %08X-%08X-%08X-%08X\n", uid[0], uid[1], uid[2], uid[3]);
  *   Serial.printf("String 128-bit UniqueID from chip: %s\n", kinetisUID());
  *   Serial.printf("Array 128-bit UUID RFC4122: %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n", uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
  *   Serial.printf("String 128-bit UUID RFC4122: %s\n", teensyUUID());
  *   }
  *
  * void loop() {}
  *
  * @endcode
  */

#ifndef TEENSYID_H
#define TEENSYID_H

#include <stdint.h>

/** Teens USB Serial Number
  *
  * @ returns
  * The USB Serial Number
  */
uint32_t teensyUsbSN();

/** Teensy Serial Number
  *
  * @param sn Pointer to an  array with size of 4 uint8_t which contents the serial number
  */
void teensySN(uint8_t *sn);

/** Teensy Serial Number
  *
  * @returns
  * A formated string in hex xx-xx-xx-xx
  */
const char* teensySN(void);

/** Teensy MAC Address
  *
  * @param mac Pointer to an array with size of 6 uint8_t which contents the mac address
  */
void teensyMAC(uint8_t *mac);

/** Teensy MAC Address
  *
  * @returns
  * A formated string in hex xx:xx:xx:xx:xx:xx
  */
const char* teensyMAC(void);

/** Kinetis Chip UID
  *
  * @param uid Pointer to an array with size of 4 uint32_t which contents the kinetis uid
  */
void kinetisUID(uint32_t *uid);

/** Kinetis Chip UID
  *
  * @returns
  * A formated string in hex xxxx:xxxx:xxxx:xxxx
  */
const char* kinetisUID(void);

/** Teensy UUID (RFC4122)
  *
  * @param mac Pointer to an array with size of 16 uint8_t which contents the uuid
  *
  * @note
  * It is an UUID extracted from the Kinetis UID and the MAC Address.
  * It is marked as version 4, (pseudo)random based
  */
void teensyUUID(uint8_t *uid);

/** Teensy UUID (RFC4122)
  *
  * @returns
  * A formated string in hex xxxx-xx-xx-xx-xxxxxx
  */
const char* teensyUUID(void);

#endif
