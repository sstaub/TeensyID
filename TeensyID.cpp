/* TeensyMAC library code is placed under the MIT license
 * Copyright (c) 2016 Frank Bösing
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

static uint32_t _getserialhw(void) {
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

#if defined(HAS_KINETIS_FLASH_FTFE) && (F_CPU > 120000000)

	extern "C" void startup_early_hook(void) {
		#if defined(KINETISK)
  		WDOG_STCTRLH = WDOG_STCTRLH_ALLOWUPDATE;
		#elif defined(KINETISL)
  		SIM_COPC = 0;  // disable the watchdog
		#endif
		*(uint32_t*)(MY_SYSREGISTERFILE) = _getserialhw();
		}

	uint32_t teensyUsbSN() {
		uint32_t num;
		num = *(uint32_t*)(MY_SYSREGISTERFILE);
		if (num < 10000000) num = num * 10;
		return num;
		}

	void teensySN(uint8_t *sn) {
		uint32_t num;
		num = *(uint32_t*)(MY_SYSREGISTERFILE);
		uint8_t *serial = (uint8_t *) &num; // itoa
		sn[0] = serial [3]; // -> little endian
		sn[1] = serial [2];
		sn[2] = serial [1];
		sn[3] = serial [0];
		}

	const char* teensySN(void) {
		uint32_t num;
		uint8_t sn[4];
		num = *(uint32_t*)(MY_SYSREGISTERFILE);
		uint8_t *serial = (uint8_t *) &num; // itoa
		sn[0] = serial [3]; // -> little endian
		sn[1] = serial [2];
		sn[2] = serial [1];
		sn[3] = serial [0];
		static char teensySerial[12];
		sprintf(teensySerial, "%02x-%02x-%02x-%02x", sn[0], sn[1], sn[2], sn[3]);
		return teensySerial;
		}

	void teensyMAC(uint8_t *mac) {
		uint64_t mac64 = 0x04E9E5000000ULL | (*(uint32_t*)(MY_SYSREGISTERFILE));
		mac[0] = mac64 >> 40;
	 	mac[1] = mac64 >> 32;
	 	mac[2] = mac64 >> 24;
	 	mac[3] = mac64 >> 16;
	 	mac[4] = mac64 >> 8;
	 	mac[5] = mac64;
		}

	const char* teensyMAC(void) {
		uint64_t mac64 = 0x04E9E5000000ULL | (*(uint32_t*)(MY_SYSREGISTERFILE));
		uint8_t mac[6];
		mac[0] = mac64 >> 40;
		mac[1] = mac64 >> 32;
		mac[2] = mac64 >> 24;
		mac[3] = mac64 >> 16;
		mac[4] = mac64 >> 8;
		mac[5] = mac64;
		static char teensyMac[18];
		sprintf(teensyMac, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		return teensyMac;
		}

#else

	uint32_t teensyUsbSN() {
		uint32_t num;
		num = _getserialhw();
		if (num < 10000000) num = num * 10;
		return num;
		}

	void teensySN(uint8_t *sn) {
		uint32_t num;
		num = _getserialhw();
		uint8_t *serial = (uint8_t *) &num; // itoa
		sn[0] = serial [3]; // -> little endian
		sn[1] = serial [2];
		sn[2] = serial [1];
		sn[3] = serial [0];
		}

	const char* teensySN(void) {
		uint32_t num;
		uint8_t sn[4];
		num = _getserialhw();
		uint8_t *serial = (uint8_t *) &num; // itoa
		sn[0] = serial [3]; // -> little endian
		sn[1] = serial [2];
		sn[2] = serial [1];
		sn[3] = serial [0];
		static char teensySerial[12];
		sprintf(teensySerial, "%02x-%02x-%02x-%02x", sn[0], sn[1], sn[2], sn[3]);
	  return teensySerial;
		}

	void teensyMAC(uint8_t *mac) {
		uint64_t mac64 = 0x04E9E5000000ULL | _getserialhw();
		mac[0] = mac64 >> 40;
	 	mac[1] = mac64 >> 32;
		mac[2] = mac64 >> 24;
	  	mac[3] = mac64 >> 16;
	  	mac[4] = mac64 >> 8;
	  	mac[5] = mac64;
		}
	const char* teensyMAC(void) {
		uint64_t mac64 = 0x04E9E5000000ULL | _getserialhw();
		uint8_t mac[6];
		mac[0] = mac64 >> 40;
	  	mac[1] = mac64 >> 32;
	  	mac[2] = mac64 >> 24;
	  	mac[3] = mac64 >> 16;
	  	mac[4] = mac64 >> 8;
	  	mac[5] = mac64;
		static char teensyMac[18];
		sprintf(teensyMac, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	  	return teensyMac;
		}
#endif

#if defined (__MKL26Z64__) // 80bit UID Teensy LC

	void kinetisUID(uint32_t *uid) {
		uid[0] = SIM_UIDMH;
  		uid[1] = SIM_UIDML;
  		uid[2] = SIM_UIDL;
		}

	const char* kinetisUID(void) {
		uint32_t uid[3];
		static char uidString[27];
		uid[0] = SIM_UIDMH;
  		uid[1] = SIM_UIDML;
  		uid[2] = SIM_UIDL;
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
		uid[0] = SIM_UIDH;
  		uid[1] = SIM_UIDMH;
  		uid[2] = SIM_UIDML;
  		uid[3] = SIM_UIDL;
  		sprintf(uidString, "%08x-%08x-%08x-%08x", uid[0], uid[1], uid[2], uid[3]);
		return uidString;
		}

#endif
