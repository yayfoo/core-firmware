/*
 * application.c
 *
 *  Created on: Apr 15, 2013
 *      Author: zsupalla
 */

#include "application.h"

void setup() {
	pinMode(0, OUTPUT);
	digitalWrite(0, LOW);
}

void loop() {
	delay(1000);
	digitalWrite(0, HIGH);
	delay(1000);
	digitalWrite(0, LOW);
}
