#pragma once

/**
 * Music Playback
 *
 * @see http://www.nongnu.org/avr-libc/user-manual/pgmspace.html
 */

// Standard C
#include <stdint.h>

// AVR
#include <avr/pgmspace.h>

// Snowlite
#include "snowlite.h"

/**
 * Magic values.
 */

// End Magic Value
#define MUSIC_END 255

/**
 * Music state machine.
 */
typedef struct {
  /**
   * Pointer to base address of scene data in flash.
   */
  const uint8_t* scene;

  /**
   * Instruction index.
   */
  uint16_t index;

  /**
   * Frequency.
   */
  uint8_t frequency;

  /**
   * Instruction duration (unit counts).
   */
  uint8_t time;

  /**
   * Time expired since loading instruction (unit counts).
   */
  uint8_t expired;
} music_state_t;

/**
 * Initialize the music state.
 */
void music_init(volatile music_state_t* state, const uint8_t* scene);

/**
 * Process a unit time step.
 */
void music_step(volatile music_state_t* state);

/**
 * Jingle Bells
 */
extern const uint8_t song_jingle_bells[] PROGMEM;

/**
 * O Christmas Tree
 */
extern const uint8_t song_christmas_tree[] PROGMEM;
