/*
 * TimedBlink basic example of usage
 *
 * Makes the built-in LED blink. 150 ms ON, 3 times, in 2 seconds
 *
 * created Feb 7, 2023
 * by Tim Braun
 *
 * This example code is in the public domain.
 */

#include <TimedBlink.h>

TimedBlink heart(LED_BUILTIN); // Use built-in LED

void setup() {
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
   // LED on for 150 ms and off for 150 ms., three times in 2 seconds
   heart.heartbeat(150, 2000-(150*5), 3); 
}

void loop() {
  heart.blink();
}
