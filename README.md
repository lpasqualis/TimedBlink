# TimedBlink Arduino library

This library was created to blink a LED without needing to use a timer.
Simply let the library know how long the LED needs to stay ON and OFF (in
milliseconds), and call .blink() as often as possible.

## Example ##

    #include <TimedBlink.h>

    TimedBlink monitor(LED_BUILTIN);

    void setup() {
      Serial.begin(9600);
      pinMode(LED_BUILTIN, OUTPUT);
      monitor.blink(150,50); // LED on for 150 ms and off for 50 ms.
    }

    void loop() {
      monitor.blink(); // Call this as often as possible
    }
