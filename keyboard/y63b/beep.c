/* beep.c

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

// toggle_count:
//  > 0 - duration specified
//  = 0 - stopped

static volatile uint32_t toggle_count;

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

void set_beep_enabled( uint8_t enable )
{
	beepEnabled = enable;
}

// frequency (in hertz) and duration (in milliseconds).
void beep(uint32_t frequency, uint32_t duration)
{
	uint8_t prescalarbits = 0b001;
	long toggles = 0;
	uint32_t ocr = 0;

	if( 0 == beepEnabled )
		return;

	if( 0 == isInitialized )
		initBeep();

	// two choices for the 16 bit timers: ck/1 or ck/64
	ocr = F_CPU / frequency / 2 - 1;

	prescalarbits = 0b001;
	if (ocr > 0xffff) {
		ocr = F_CPU / frequency / 2 / 64 - 1;
		prescalarbits = 0b011;
	}

	TCCR3B = (TCCR3B & 0b11111000) | prescalarbits;

	// Calculate the toggle count
	toggles = 2 * frequency * duration / 1000;

	// Set the OCR for the given timer,
	// set the toggle count,
	// then turn on the interrupts
	OCR3A = ocr;
	toggle_count = toggles;
	TIMSK3 |= (1u<<OCIE3A);
}

ISR(TIMER3_COMPA_vect)
{
	if (toggle_count != 0) {
		// toggle the pin
		BEEP_PORT ^= BEEP_PIN_MASK;
		toggle_count--;
	} else {
		TIMSK3 &= ~(1u<<OCIE3A);
		BEEP_PORT &= ~(BEEP_PIN_MASK);  // keep pin low after stop
	}
}
