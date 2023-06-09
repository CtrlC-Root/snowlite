// Standard C
#include <stdbool.h>

// Snowlite
#include "music.h"
#include "notes.h"

// Load the current instruction.
void music_load(volatile music_state_t* state) {
  uint16_t offset = state->index * 2;

  state->frequency = pgm_read_byte(&state->scene[offset + 0]);
  state->time = pgm_read_byte(&state->scene[offset + 1]);
}

// Initialize the music state.
void music_init(volatile music_state_t* state, const uint8_t* scene) {
  // initialize state
  state->scene = scene;
  state->index = 0;
  state->expired = 0;

  // load initial instruction
  music_load(state);
}

// Process a unit time step.
void music_step(volatile music_state_t* state) {
  // keep track of expired time
  state->expired++;

  // check if we need to load the next instruction
  if (state->expired >= state->time) {
    // load the next instruction
    state->index++;
    state->expired = 0;
    music_load(state);

    // determine if we're at the end of the scene
    bool last_instruction = (state->frequency == MUSIC_END)
      || (state->time == MUSIC_END);

    // repeat from the beginning if we're at the end
    if (last_instruction) {
      state->index = 0;
      music_load(state);
    }
  }
}

// Jingle Bells
const uint8_t song_jingle_bells[] PROGMEM = {
  // first line (14)
  NOTE_D4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_G4, BEAT_10,

  NOTE_D4, BEAT_30,
  NOTE_D4, BEAT_05,
  NOTE_D4, BEAT_05,

  NOTE_D4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_G4, BEAT_10,

  NOTE_E4, BEAT_30,
  NOTE_REST, BEAT_10,

  // second line (12)
  NOTE_E4, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,

  NOTE_FS4, BEAT_30,
  NOTE_REST, BEAT_10,

  NOTE_D5, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_A4, BEAT_10,

  NOTE_B4, BEAT_30,
  NOTE_D4, BEAT_10,

  // third line (12)
  NOTE_D4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_G4, BEAT_10,

  NOTE_D4, BEAT_30,
  NOTE_D4, BEAT_10,

  NOTE_D4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_G4, BEAT_10,

  NOTE_E4, BEAT_30,
  NOTE_E4, BEAT_10,

  // fourth line (14)
  NOTE_E4, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,

  NOTE_D5, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_D5, BEAT_10,

  NOTE_E5, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_A4, BEAT_10,

  NOTE_G4, BEAT_20,
  NOTE_REST, BEAT_20,

  // chorus line 1
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_20,

  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_20,

  NOTE_B4, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_G4, BEAT_15,
  NOTE_A4, BEAT_05,

  NOTE_B4, BEAT_40,

  // chorus line 2
  NOTE_C5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_C5, BEAT_15,
  NOTE_C5, BEAT_05,

  NOTE_C5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_05,
  NOTE_B4, BEAT_05,

  NOTE_B4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_B4, BEAT_10,

  NOTE_A4, BEAT_20,
  NOTE_D5, BEAT_20,

  // chorus line 3
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_20,

  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_20,

  NOTE_B4, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_G4, BEAT_15,
  NOTE_A4, BEAT_05,

  NOTE_B4, BEAT_40,

  // chorus line 4
  NOTE_C5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_C5, BEAT_15,
  NOTE_C5, BEAT_05,

  NOTE_C5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_05,
  NOTE_B4, BEAT_05,

  NOTE_D5, BEAT_10,
  NOTE_D5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_A4, BEAT_10,

  NOTE_G4, BEAT_40,

  // end
  MUSIC_END, MUSIC_END
};

// O Christmas Tree
const uint8_t song_christmas_tree[] PROGMEM = {

  // song is in 3/4 time

  // first line (15)
  NOTE_REST, BEAT_10,
  NOTE_REST, BEAT_10,
  NOTE_D4, BEAT_20,

  NOTE_G4, BEAT_15,
  NOTE_G4, BEAT_05,
  NOTE_G4, BEAT_20,
  NOTE_A4, BEAT_20,

  NOTE_B4, BEAT_15,
  NOTE_B4, BEAT_05,
  NOTE_B4, BEAT_30,
  NOTE_B4, BEAT_10,

  NOTE_A4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_C5, BEAT_20,
  NOTE_FS4, BEAT_20,

  // second line (15)
  NOTE_A4, BEAT_20,
  NOTE_G4, BEAT_20,
  NOTE_D4, BEAT_20,

  NOTE_G4, BEAT_15,
  NOTE_G4, BEAT_05,
  NOTE_G4, BEAT_20,
  NOTE_A4, BEAT_20,

  NOTE_B4, BEAT_15,
  NOTE_B4, BEAT_05,
  NOTE_B4, BEAT_30,
  NOTE_B4, BEAT_10,

  NOTE_A4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_C5, BEAT_20,
  NOTE_FS4, BEAT_20,

  // third line (15)
  NOTE_A4, BEAT_20,
  NOTE_G4, BEAT_30,
  NOTE_D5, BEAT_10,

  NOTE_D5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_E5, BEAT_30,
  NOTE_D5, BEAT_10,

  NOTE_D5, BEAT_10,
  NOTE_C5, BEAT_10,
  NOTE_C5, BEAT_30,
  NOTE_C5, BEAT_10,

  NOTE_C5, BEAT_10,
  NOTE_A4, BEAT_10,
  NOTE_D5, BEAT_30,
  NOTE_C5, BEAT_10,

  // fourth line (19)
  NOTE_C5, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_B4, BEAT_20,
  NOTE_D4, BEAT_20,

  NOTE_G4, BEAT_15,
  NOTE_G4, BEAT_05,
  NOTE_G4, BEAT_20,
  NOTE_A4, BEAT_20,

  NOTE_B4, BEAT_15,
  NOTE_B4, BEAT_05,
  NOTE_B4, BEAT_30,
  NOTE_B4, BEAT_10,

  NOTE_A4, BEAT_10,
  NOTE_B4, BEAT_10,
  NOTE_C5, BEAT_20,
  NOTE_FS4, BEAT_20,

  NOTE_A4, BEAT_20,
  NOTE_G4, BEAT_20,
  NOTE_REST, BEAT_20,

  // end
  MUSIC_END, MUSIC_END
};
