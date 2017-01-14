/*
 * TimedBlink basic example of usage
 *
 * Makes the built-in LED blink. 200ms ON and 100ms OFF.
 *
 * created January 14, 2017
 * by Lorenzo Pasqualis
 *
 * This example code is in the public domain.
 */
 
#include <TimedBlink.h>

TimedBlink monitor(LED_BUILTIN);

void setup() {
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
   monitor.blink(200,100);
}

void loop() {
  monitor.blink();
}

