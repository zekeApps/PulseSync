// Pulse Sync for costuritas
#include "main.h"
#include "util.h"
unsigned long period = 500;

void setup() {
	Serial.begin(9600);
	pinMode(syncPulsePin, OUTPUT);
}

void loop() {
	period = getPeriodUpdate(period);
	syncPulse(syncPulsePin, period);
	}
