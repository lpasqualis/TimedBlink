///
/// A library to handle a blinking LED
///

#include <Arduino.h>
#include <cstdint>
#include "TimedBlink.h"

#define dbg(...)

/*
 * Resets all timers and state
 */
void TimedBlink::reset() {
  m_blinkTime   = 0UL;
  m_onForTime   = 0;
  m_offForTime  = 0;
  m_blinkState  = BLINK_OFF;
  m_resolution  = 100;
  m_beating = false;
}

/*
 * Constructor. Only needs to know what pin to blink.
 */
TimedBlink::TimedBlink(int pin) :
	m_beating(false),
	m_blinkState(BLINK_OFF),
	m_pin(pin),
	m_resolution(0)
{
  reset();
}

/*
 * Sets the blink time ON
 */
void TimedBlink::setOnTime(int ms) {
  if (ms > 0) { // no=op if ms is <= 0
    m_onForTime = ms;
    if (m_offForTime > 0) {
      m_resolution = min(m_onForTime,m_offForTime)/10;
    }
  }
}

/*
 * Sets the blink time OFF
 */
void TimedBlink::setOffTime(int ms) {
  if (ms > 0) { // no=op if ms is <= 0
    m_offForTime = ms;
    if (m_onForTime > 0) {
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
 * Executes the blink. It allows to specify new on and off times. Use zeroes
 * or negative values if you don't want to change what is already set.
 */
void TimedBlink::blink(int on_for, int off_for) {

  uint32_t ct = millis();

  if (m_blinkTime==0UL)
  	m_blinkTime=ct;

  uint32_t diff = (ct - m_blinkTime);

  setOnTime(on_for);
  setOffTime(off_for);

  if (m_blinkState == BLINK_OFF && (m_offForTime > 0 || m_beating)) {
		if (m_beating) {
			if (diff >= (uint32_t )m_onForTime && m_beatState < m_beatCount) {
		  		setBlinkState(BLINK_ON);
				m_beatState++;
				dbg("OFF -> ON beating state %u\n", m_beatState);
			}
			else if ((m_offForTime > 0) && (diff >= (uint32_t)m_offForTime)) {
				setBlinkState(BLINK_ON);
				m_beatState = 1;
				dbg("OFF -> ON beating state %u\n", m_beatState);
			}
		}

		else if (diff >= (uint32_t )m_offForTime) {
		  setBlinkState(BLINK_ON);
		}
  }
  else if (m_blinkState == BLINK_ON && m_onForTime > 0) {
		if (diff >= (uint32_t )m_onForTime) {
			setBlinkState(BLINK_OFF);

			if (m_beating) {
				m_beatState++;
				dbg("ON -> OFF beating state %u\n", m_beatState);
			}
		}

  }
}

/*
 * Call often to blink.
 */
void TimedBlink::loop() {
  blink();
}

/*
 * Equivalent to delay(d), but updates the blink.
 */
void TimedBlink::blinkDelay(int d)
{
  unsigned long ct = millis();
  while (millis()-ct < (uint32_t)d) {
    blink();
	yield();
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

/*
 * Sets up a heartbeat pattern
 */
void TimedBlink::heartbeat(uint32_t on,
		uint32_t off, uint32_t count)
{
	reset();

	m_beating = true;
	m_beatState = 1;
	m_onForTime = on;
	m_offForTime = off;
	m_beatCount = count * 2;	// On/Off for each beat
}
