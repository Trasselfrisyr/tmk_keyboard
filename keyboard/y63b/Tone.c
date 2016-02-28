/* Tone.c

	Buzzer for keyboard to simulate some strange Luxor computer.

	Based on Tone.cpp from Arduino lib.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// timerx_toggle_count:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)

static volatile long timer_toggle_count;

static uint8_t isInitialized = 0;

static uint8_t beepEnabled = 1;

#define BEEP_PIN_MASK (1<<7u)
#define BEEP_PORT 	PORTC
#define BEEP_DDR    DDRC


static void initBeep(void)
{
	TCCR3A = 0;
	TCCR3B = 0;
	TCCR3B |= (1u<<WGM32) | (1u<<CS30);
	BEEP_DDR |= BEEP_PIN_MASK;
	isInitialized = 1;
}


// frequency (in hertz) and duration (in milliseconds).
void beep(unsigned int frequency, unsigned long duration)
{
	uint8_t prescalarbits = 0b001;
	long toggle_count = 0;
	uint32_t ocr = 0;

	if( 0 == beepEnabled )
		return;

	if( 0 == isInitialized )
		initBeep();

	// two choices for the 16 bit timers: ck/1 or ck/64
	ocr = F_CPU / frequency / 2 - 1;

	prescalarbits = 0b001;
	if (ocr > 0xffff)
	{
		ocr = F_CPU / frequency / 2 / 64 - 1;
		prescalarbits = 0b011;
	}
	TCCR3B = (TCCR3B & 0b11111000) | prescalarbits;

	// Calculate the toggle count
	if (duration > 0)
	{
		toggle_count = 2 * frequency * duration / 1000;
	}
	else
	{
		toggle_count = -1;
	}

	// Set the OCR for the given timer,
	// set the toggle count,
	// then turn on the interrupts
	OCR3A = ocr;
	timer_toggle_count = toggle_count;
	TIMSK3 |= (1u<<OCIE3A);
}


// XXX: this function only works properly for timer 2 (the only one we use
// currently).  for the others, it should end the tone, but won't restore
// proper PWM functionality for the timer.
inline
static void disableTimer(void)
{
	TIMSK3 &= ~(1u<<OCIE3A);
}


void noTone(uint8_t _pin)
{
	disableTimer();
	BEEP_PORT &= ~BEEP_PIN_MASK;
}


ISR(TIMER3_COMPA_vect)
{
	if (timer_toggle_count != 0)
	{
		// toggle the pin
		BEEP_PORT ^= BEEP_PIN_MASK;

		if (timer_toggle_count > 0)
			timer_toggle_count--;
	}
	else
	{
		disableTimer();
		BEEP_PORT &= ~(BEEP_PIN_MASK);  // keep pin low after stop
	}
}

