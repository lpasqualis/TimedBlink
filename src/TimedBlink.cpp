#include <Arduino.h>
#include "TimedBlink.h"

/*
 * Resets all timers and state
 */
void TimedBlink::reset() {
  m_blinkTime   = 0UL;
  m_onForTime   = -1;
  m_offForTime  = -1;
  m_blinkState  = BLINK_OFF;
  m_resolution  = 100;
}

/*
 * Constructor. Only needs to know what pin to blink.
 */
TimedBlink::TimedBlink(int pin) {
  m_pin = pin;
  reset();
}

/*
 * Sets the blink time ON
 */
void TimedBlink::setOnTime(int ms) {
  if (ms>0) { // no=op if ms is <= 0
    m_onForTime = ms;
    if (m_offForTime>0) {
      m_resolution = min(m_onForTime,m_offForTime)/10;
    }
  }
}

/*
 * Sets the blink time OFF
 */
void TimedBlink::setOffTime(int ms) {
  if (ms>0) { // no=op if ms is <= 0
    m_offForTime = ms;
    if (m_onForTime>0) {
      m_resolution = min(m_onForTime,m_offForTime);
    }
  }
}

/*
 * Sets the blink state ON or OFF
 */
void TimedBlink::setBlinkState(blink_t state)
{
  digitalWrite(m_pin, (state==BLINK_ON) ? HIGH : LOW);
  m_blinkState = state;
  m_blinkTime  = millis();
}

/*
 * Executes the blink. It allows to specify new on and off times. Use negative
 * values if you don't want to change what is already set.
 */

void TimedBlink::blink(int on_for, int off_for) {

  unsigned long ct = millis();
  if (m_blinkTime==0UL) m_blinkTime=ct;
  unsigned long diff = abs(ct - m_blinkTime);
  short set_to = -1;

  setOnTime(on_for);
  setOffTime(off_for);

  if (m_blinkState==BLINK_OFF) {
    if (m_offForTime>0 && diff>m_offForTime) {
      setBlinkState(BLINK_ON);
    }
  } else {
    if (m_onForTime>0 && diff>m_onForTime) {
      setBlinkState(BLINK_OFF);
    }
  }
}

/*
 * Call often to blink.
 */
void TimedBlink::blink() {
  blink(-1,-1);
}

/*
 * Equivalent to delay(d), but updates the blink.
 */
void TimedBlink::blinkDelay(int d)
{
  unsigned long ct = millis();
  while (millis()-ct<d) {
    blink();
    delay(m_resolution);
  }
}

/*
 * Turns off the blink.
 */
void TimedBlink::blinkOff() {
  reset();
  digitalWrite(m_pin, LOW);
}
