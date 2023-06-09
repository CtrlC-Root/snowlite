#pragma once

/**
 * Light Playback
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

// Off
#define LIGHT_OFF 0

// Maximum Brightness
#define LIGHT_MAX 254

// End Magic Value
#define LIGHT_END 255

/**
 * Light state machine.
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
   * Light 1 value.
   */
  uint8_t led1;

  /**
   * Light 2 value.
   */
  uint8_t led2;

  /**
   * Instruction duration (unit counts).
   */
  uint8_t time;

  /**
   * Time expired since loading instruction (unit counts).
   */
  uint8_t expired;
} light_state_t;

/**
 * Initialize the light state.
 */
void light_init(volatile light_state_t* state, const uint8_t* scene);

/**
 * Process a unit time step.
 */
void light_step(volatile light_state_t* state);

/**
 * Blinking Lights
 */
extern const uint8_t scene_blinking_lights[] PROGMEM;
