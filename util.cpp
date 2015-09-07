#include "main.h"

unsigned long getPeriodUpdate(unsigned long period) {
	char dataIn[7] = { 0 };
	
	if (Serial.available() > 0) {
		Serial.readBytesUntil(0x0A, dataIn, sizeof(dataIn));				  // 0x0A is a new Line feed char 
		period = atoi(dataIn);
		Serial.println(period);
	}
	return period;
}

void syncPulse(int Pin, unsigned long awaitMS) {
	digitalWrite(Pin, HIGH);
	delay(awaitMS);
	digitalWrite(Pin, LOW);
	delay(awaitMS);
}

int Debug(char *str, ...) {

	
	int i, j, count = 0;

	va_list argv;
	va_start(argv, str);
	for (i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] == '%') {
			count++;

			Serial.write(reinterpret_cast<const uint8_t*>(str + j), i - j);

			switch (str[++i]) {
			case 'd': Serial.print(va_arg(argv, int));
				break;
			case 'l': Serial.print(va_arg(argv, long));
				break;
			case 'f': Serial.print(va_arg(argv, double));
				break;
			case 'c': Serial.print((char)va_arg(argv, int));
				break;
			case 's': Serial.print(va_arg(argv, char *));
				break;
			case '%': Serial.print("%");
				break;
			default:;
			};

			j = i + 1;
		}
	};
	va_end(argv);

	if (i > j) {
		Serial.write(reinterpret_cast<const uint8_t*>(str + j), i - j);
	}

	return count;
	


}