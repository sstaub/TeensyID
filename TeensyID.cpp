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

#include "TeensyID.h"
#include <Arduino.h>

#define MY_SYSREGISTERFILE	((uint8_t *)0x40041000) // System Register File

static uint32_t getTeensySerial(void) {
	uint32_t num;
	__disable_irq();
	#if defined(HAS_KINETIS_FLASH_FTFA) || defined(HAS_KINETIS_FLASH_FTFL)
		FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
		FTFL_FCCOB0 = 0x41;
		FTFL_FCCOB1 = 15;
		FTFL_FSTAT = FTFL_FSTAT_CCIF;
		while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
		num = *(uint32_t *)&FTFL_FCCOB7;
	#elif defined(HAS_KINETIS_FLASH_FTFE)
		kinetis_hsrun_disable();
		FTFL_FSTAT = FTFL_FSTAT_RDCOLERR | FTFL_FSTAT_ACCERR | FTFL_FSTAT_FPVIOL;
		*(uint32_t *)&FTFL_FCCOB3 = 0x41070000;
		FTFL_FSTAT = FTFL_FSTAT_CCIF;
		while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF)) ; // wait
		num = *(uint32_t *)&FTFL_FCCOBB;
		kinetis_hsrun_enable();
	#endif
	__enable_irq();
	return num;
	}

	uint32_t teensyUsbSN() {
		uint32_t num = getTeensySerial();
		if (num < 10000000) num = num * 10;
		return num;
		}

	void teensySN(uint8_t *sn) {
		uint32_t num = getTeensySerial();
		sn[0] = num >> 24;
		sn[1] = num >> 16;
		sn[2] = num >> 8;
		sn[3] = num;
		}

	const char* teensySN(void) {
		uint8_t serial[4];
		static char teensySerial[12];
		teensySN(serial);
		sprintf(teensySerial, "%02x-%02x-%02x-%02x", serial[0], serial[1], serial[2], serial[3]);
		return teensySerial;
		}

	void teensyMAC(uint8_t *mac) {
		uint8_t serial[4];
		teensySN(serial);
		mac[0] = 0x04;
		mac[1] = 0xE9;
		mac[2] = 0xE5;
		mac[3] = serial[1];
		mac[4] = serial[2];
		mac[5] = serial[3];
		}

	const char* teensyMAC(void) {
		uint8_t mac[6];
		static char teensyMac[18];
		teensyMAC(mac);
		sprintf(teensyMac, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		return teensyMac;
		}

#if defined (__MKL26Z64__) // 80bit UID Teensy LC

	void kinetisUID(uint32_t *uid) {
		uid[0] = SIM_UIDMH;
		uid[1] = SIM_UIDML;
		uid[2] = SIM_UIDL;
		}

	const char* kinetisUID(void) {
		uint32_t uid[3];
		static char uidString[27];
		kinetisUID(uid);
		sprintf(uidString, "%08x-%08x-%08x", uid[0], uid[1], uid[2]);
		return uidString;
	}

#elif defined (__MK20DX128__) || defined (__MK20DX256__) || defined (__MK64FX512__) || defined (__MK66FX1M0__) // 128bit UID Teensy 3.0, 3.1, 3.2, 3.5, 3.6

	void kinetisUID(uint32_t *uid) {
  	uid[0] = SIM_UIDH;
  	uid[1] = SIM_UIDMH;
  	uid[2] = SIM_UIDML;
  	uid[3] = SIM_UIDL;
		}

	const char* kinetisUID(void) {
		uint32_t uid[4];
		static char uidString[36];
		kinetisUID(uid);
  	sprintf(uidString, "%08x-%08x-%08x-%08x", uid[0], uid[1], uid[2], uid[3]);
		return uidString;
	}

#endif

void teensyUUID(uint8_t *uuid) {
	uint8_t mac[6];
	teensyMAC(mac);
	uuid[0] = SIM_UIDML >> 24;
	uuid[1] = SIM_UIDML >> 16;
	uuid[2] = SIM_UIDML >> 8;
	uuid[3] = SIM_UIDML;
	uuid[4] = SIM_UIDL >> 24;
	uuid[5] = SIM_UIDL >> 16;
	uuid[6] = 0x40; // marked as version v4, but this uuid is not random based !!!
	uuid[7] = SIM_UIDL >> 8;
	uuid[8] = 0x80; //variant
	uuid[9] = SIM_UIDL;
	uuid[10] = mac[0];
	uuid[11] = mac[1];
	uuid[12] = mac[2];
	uuid[13] = mac[3];
	uuid[14] = mac[4];
	uuid[15] = mac[5];
	}

const char* teensyUUID(void) {
	uint8_t uuid[16];
	static char uuidString[37];
	teensyUUID(uuid);
	sprintf(uuidString, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
	return uuidString;
	}
