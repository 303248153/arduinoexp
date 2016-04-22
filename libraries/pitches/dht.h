// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// 0.1.01 added support for Arduino 1.0, fixed typos (31/12/2011)
// 0.1.0 by Rob Tillaart (01/04/2011)
// inspired by DHT11 library
//
// HISTORY (Redistributed)
// 2016-04-22 translate to c and header only code
//
#pragma once
#define DHT_WAIT_TIMEOUT 10000

// wait pin state to be LOW or HIGH
// 0: ok
// -2: timeout
static int dht_wait(int pin, int state) {
	for (int i = 0; i < DHT_WAIT_TIMEOUT; ++i) {
		if (digitalRead(pin) == state) {
			return 0;
		}
	}
	return -2;
}

// return values:
// 0: ok
// -2: timeout
static int dht_read(int pin, uint8_t bits[5]) {
	// empty buffer
	memset(bits, 0, sizeof(uint8_t)*5);

	// request sample
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	// get acknowledge or timeout
	if (dht_wait(pin, HIGH) != 0) {
		return -2;
	}
	if (dht_wait(pin, LOW) != 0) {
		return -2;
	}

	// read the output, 40bits => 5 bytes
	for (int i = 0; i < 5; ++i) {
		for (int j = 7; j >= 0; --j) {
			if (dht_wait(pin, HIGH) != 0) {
				return -2;
			}
			unsigned long t = micros();
			if (dht_wait(pin, LOW) != 0) {
				return -2;
			}
			if (micros() - t > 40) {
				bits[i] |= 1 << j;
			}
		}
	}
	return 0;
}

// read dht11
// 0: ok
// -1: checksum error
// -2: timeout
static int dht_read11(int pin, int* temperature, int* humidity) {
	// read bits
	uint8_t bits[5];
	int ret = dht_read(pin, bits);
	if (ret != 0) {
		return ret;
	}

	// convert to values
	*humidity = bits[0]; // bits[1] is 0
	*temperature = bits[2]; // bits[3] is 0

	// test checksum
	uint8_t sum = *humidity + *temperature;
	if (bits[4] != sum) {
		return -1;
	}
	return 0;
}

// read dht22
// 0: ok
// -1: checksum error
// -2: timeout
static int dht_read22(int pin, float* temperature, float* humidity) {
	// read bits
	uint8_t bits[5];
	int ret = dht_read(pin, bits);
	if (ret != 0) {
		return ret;
	}

	// convert to values
	*humidity = ((bits[0] << 8) + bits[1]) * 0.1;
	int sign = (bits[2] & 0x80) ? -1 : 1;
	*temperature = sign * (((bits[2] & 0x7f) << 8) + bits[3]) * 0.1;

	// test checksum
	uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
	if (bits[4] != sum) {
		return -1;
	}
	return 0;
}
