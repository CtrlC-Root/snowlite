// Standard C
#include <stdbool.h>

// Snowlite
#include "light.h"

// Load the current instruction.
void light_load(volatile light_state_t* state) {
  uint16_t offset = state->index * 3;

  state->led1 = pgm_read_byte(&state->scene[offset + 0]);
  state->led2 = pgm_read_byte(&state->scene[offset + 1]);
  state->time = pgm_read_byte(&state->scene[offset + 2]);
}

// Initialize the light state.
void light_init(volatile light_state_t* state, const uint8_t* scene) {
  // initialize state
  state->scene = scene;
  state->index = 0;
  state->expired = 0;

  // load initial instruction
  light_load(state);
}

// Process a unit time step.
void light_step(volatile light_state_t* state) {
  // keep track of expired time
  state->expired++;

  // check if we need to load the next instruction
  if (state->expired >= state->time) {
    // load the next instruction
    state->index++;
    state->expired = 0;
    light_load(state);

    // determine if we're at the end of the scene
    bool last_instruction = (state->led1 == LIGHT_END)
      || (state->led2 == LIGHT_END)
      || (state->time == LIGHT_END);

    // repeat from the beginning if we're at the end
    if (last_instruction) {
      state->index = 0;
      light_load(state);
    }
  }
}

// Blinking Lights
const uint8_t scene_blinking_lights[] PROGMEM = {
  LIGHT_OFF,  LIGHT_MAX,  BEAT_10,
  64,         196,        BEAT_10,
  128,        128,        BEAT_10,
  196,        64,         BEAT_10,
  LIGHT_MAX,  LIGHT_OFF,  BEAT_10,
  LIGHT_END,  LIGHT_END,  LIGHT_END
};
