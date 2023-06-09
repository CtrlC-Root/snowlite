#pragma once

/**
 * Hardware Management
 */

 // Standard C
 #include <stdint.h>

/**
 * Speaker volume levels.
 */
typedef enum {
  VOLUME_OFF,
  VOLUME_ON
} volume_t;

/**
 * Initialize the board hardware.
 */
void board_init();

/**
 * Set LED values. For LEDs that aren't connected to a PWM output this will
 * turn them on if the value is greater than 127 and off otherwise.
 */
void board_set_leds(uint8_t led1, uint8_t led2, uint8_t led3);

/**
 * Set speaker values.
 */
void board_set_speaker(uint8_t frequency, volume_t volume);
