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

#ifndef TEENSYID_H
#define TEENSYID_H

#include "Arduino.h"

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
  * @param uid Pointer to an array with size of 16 uint8_t which contents the uuid
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

/** Teensy UID 64-bit for Teensy 4.x
  *
  * @param uid Pointer to an array with size of 16 uint8_t which contents the uuid
  *
  * @note
  * It is an UUID extracted from the Kinetis UID and the MAC Address.
  * It is marked as version 4, (pseudo)random based
  */
void teensyUID64(uint8_t *uid64);

/** Teensy UID 64-bit for Teensy 4.x
  *
  * @returns
  * A formated string in hex xxxx-xx-xx-xx-xxxxxx
  */
const char* teensyUID64(void);

#endif
