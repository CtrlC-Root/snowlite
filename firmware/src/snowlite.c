/**
 * Snowlite
 *
 * PB0 - LED1 (Timer 0 - OC0A)
 * PB1 - LED2 (Timer 0 - OC0B)
 * PB2 - SW1 (INT0)
 * PB3 - LED3 (Digital Output)
 * PB4 - Piezo (Timer 1 - OC1B)
 */

// Standard C
#include <stdint.h>
#include <stdbool.h>

// AVR
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Snowlite
#include "board.h"
#include "light.h"
#include "music.h"
#include "notes.h"

/**
 * Clock wall time (milliseconds).
 */
volatile uint32_t clock_time;

/**
 * Operating states.
 */
typedef enum {
  OFF,
  LOW,
  HIGH,
  BLINK,
  JINGLE_BELLS,
  CHRISTMAS_TREE
} snowlite_state_t;

/**
 * Current state.
 */
volatile snowlite_state_t snowlite_state;

/**
 * Light state machine.
 */
volatile light_state_t light_state;

/**
 * Music state machine.
 */
volatile music_state_t music_state;

/**
 * Button state.
 */
volatile uint16_t button_state;

/**
 * Button timeout.
 */
volatile uint32_t button_timeout;

/**
 * Change the current state.
 */
void set_state(snowlite_state_t next_state) {
  // disable LEDs and speaker
  board_set_leds(LIGHT_OFF, LIGHT_OFF, LIGHT_OFF);
  board_set_speaker(NOTE_REST, VOLUME_OFF);

  // enter next state
  snowlite_state = next_state;
  switch (snowlite_state) {
    case OFF: {
      // TODO: power down sleep
    }; break;

    case LOW: {
      board_set_leds(128, 128, 128);
    }; break;

    case HIGH: {
      board_set_leds(LIGHT_MAX, LIGHT_MAX, LIGHT_MAX);
    }; break;

    case BLINK: {
      // initialize scene
      light_init(&light_state, &scene_blinking_lights[0]);
    }; break;

    case JINGLE_BELLS: {
      // initialize scene
      light_init(&light_state, &scene_blinking_lights[0]);
      music_init(&music_state, &song_jingle_bells[0]);
    }; break;

    case CHRISTMAS_TREE: {
      // initialize scene
      light_init(&light_state, &scene_blinking_lights[0]);
      music_init(&music_state, &song_christmas_tree[0]);
    }; break;
  }
}

/**
 * Run the current state.
 */
void process_state() {
  // process the state
  switch (snowlite_state) {
    case BLINK: {
      // update state machines
      light_step(&light_state);

      // update LEDs
      board_set_leds(light_state.led1, light_state.led2, LIGHT_MAX);
    }; break;

    case JINGLE_BELLS:
    case CHRISTMAS_TREE: {
      // update state machines
      light_step(&light_state);
      music_step(&music_state);

      // update LEDs
      board_set_leds(light_state.led1, light_state.led2, LIGHT_MAX);

      // update speaker
      if (music_state.expired == 0) {
        // insert a brief rest at the beginning of each note
        board_set_speaker(NOTE_REST, VOLUME_OFF);
      }
      else {
        board_set_speaker(music_state.frequency, VOLUME_ON);
      }
    }; break;
  }
}

/**
 * Switch to the next state.
 */
void next_state() {
  switch (snowlite_state) {
    case OFF:             set_state(LOW);             break;
    case LOW:             set_state(HIGH);            break;
    case HIGH:            set_state(BLINK);           break;
    case BLINK:           set_state(JINGLE_BELLS);    break;
    case JINGLE_BELLS:    set_state(CHRISTMAS_TREE);  break;
    case CHRISTMAS_TREE:  set_state(OFF);             break;
  }
}

/**
 * Timer 0 Overflow Interrupt
 */
ISR(TIM0_OVF_vect) {
  // keep track of time
  clock_time += TIMER_PERIOD_MS;

  // sample button input and check for press
  button_state = (button_state << 1) | (bit_is_set(PINB, PB2) > 0);
  uint16_t button_check = button_state & 0b1110000000011111; // mask out inner bits
  button_check = button_check == 0b1110000000000000; // high then low period

  if (button_check && button_timeout <= clock_time) {
    // button was pressed
    button_state = 0x0000;
    button_timeout = clock_time + 480;

    // next state
    next_state();
  }

  // process the current state
  if (clock_time % TIME_UNIT_MS == 0) {
    process_state();
  }
}

/**
 * Application entry point.
 */
void main() {
  // initialize hardware
  board_init();

  // configure idle sleep mode, everything except cpu and flash
  set_sleep_mode(0);

  // initialize state
  clock_time = 0;
  button_timeout = 0;
  button_state = 0;
  snowlite_state = OFF;

  // enter initial state
  set_state(LOW);

  // enable interrupts
  sei();

  // always enter sleep mode
  while (true) {
    sleep_mode();
  }
}
