// AVR
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Snowlite
#include "board.h"

// Initialize the board hardware.
void board_init() {
  // configure output pins
  DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB3) | (1<<PB4);

  // configure input pins (with pull-up resistors)
  DDRB &= ~(1<<PB2); // (default)
  PORTB |= (1<<PB2); // enable pull-up resistors

  // configure external interrupt 0
  MCUCR &= ~(1<<ISC00) & ~(1<<ISC01); // (default) interrupt on low level
  // GIMSK |= (1<<INT0); // enable INT0 interrupt

  // configure timer / counter 0
  TCCR0A |= (1<<WGM00); // phase correct PWM mode, 0x00 to 0xFF
  TCCR0B |= (1<<CS01); // internal clock, 1/8 prescaling
  TIMSK |= (1<<TOIE0); // enable overflow interrupt
  TCCR0A |= (1<<COM0A1) | (1<<COM0B1); // OC0A, OC0B

  // configure timer / counter 1
  GTCCR |= (1<<PWM1B); // PWM mode (OC1B)
  TCCR1 |= (1<<CS10) | (1<<CS12); // internal clock, 1/16 prescaling
  GTCCR |= (1<<COM1B1); // OC1B clear on OCR1B, set on 0x00

  // initialize peripherals
  board_set_leds(0, 0, 0);
  board_set_speaker(255, VOLUME_OFF);
}

// Set LED values.
void board_set_leds(uint8_t led1, uint8_t led2, uint8_t led3) {
  // PWM controlled LEDs
  OCR0A = led1; // Timer 0 - OC0A
  OCR0B = led2; // Timer 0 - OC0B

  // DIO controlled LEDs
  if (led3 > 127) {
    PORTB |= (1<<PB3);
  }
  else {
    PORTB &= ~(1<<PB3);
  }
}

// Set speaker values.
void board_set_speaker(uint8_t frequency, volume_t volume) {
  // top value controls frequency
  OCR1C = frequency; // Timer 1 - MAX

  // duty cycle controls volume
  switch (volume) {
    case VOLUME_OFF: {
      // hold output low
      OCR1B = 0; // Timer 1 - OC1B
    }; break;

    case VOLUME_ON: {
      // 50% duty cycle
      OCR1B = OCR1C / 2; // Timer 1 - OC1B
    }; break;
  }
}
