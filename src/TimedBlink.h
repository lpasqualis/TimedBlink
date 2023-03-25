
#ifndef __TimedBlink__H__
#define __TimedBlink__H__

#include <Arduino.h>

enum blink_t {BLINK_ON, BLINK_OFF};

class TimedBlink {
  private:
    unsigned long m_blinkTime;
    int m_onForTime;
    int m_offForTime;
	uint32_t m_beatTime;
	uint32_t m_beatCount;
	uint32_t m_beatState;
	bool m_beating;
    blink_t m_blinkState;
    short m_pin;
    int m_resolution;

    void reset();

  public:

    TimedBlink(int pin);
    void blink(int on_for = -1, int off_for = -1);
	void loop(void);
    void setOnTime(int ms);
    void setOffTime(int ms);
    void setBlinkState(blink_t state);
    void blinkDelay(int d);
    void blinkOff();
    void heartbeat(uint32_t on = 200,
		uint32_t off = 1000 - (3*200), uint32_t count = 2);
    inline void oneshot(int ms) { setOnTime(ms); setBlinkState(BLINK_ON); };
    inline void heartbeat_oneshot(int ms, uint32_t count) {
        heartbeat(ms, 0, count); setBlinkState(BLINK_ON);
    };
};

#endif // __TimedBlink__H__
