#pragma once

// Standard C
#include <math.h> // round()

/**
 * Timer prescale factor.
 */
#define TIMER_PRESCALE 8

/**
 * Timer frequency in Phase Correct PWM Mode. This assumes the F_CPU value
 * is defined to represent the system clock in Hz. The F_CPU value is also
 * used by the <util/delay.h> functions to generate accurate delays.
 *
 * @see datasheet pg. 75
 */
#define TIMER_FREQ_HZ ((int) round(F_CPU / (TIMER_PRESCALE * 510)))

/**
 * Timer period.
 */
#define TIMER_PERIOD_MS ((int) round(1000 / TIMER_FREQ_HZ))

/**
 * Unit time for light and music playback.
 */
#define TIME_UNIT_MS (TIMER_PERIOD_MS * 5)

/**
 * Light times (periods).
 */
#define TIME_SECOND ((int) round(1000 / TIME_UNIT_MS))

/**
 * Music beat times (periods).
 */
#define BEAT_05 (160 / TIME_UNIT_MS)
#define BEAT_10 (BEAT_05 * 2)
#define BEAT_15 (BEAT_10 + BEAT_05)
#define BEAT_20 (BEAT_10 * 2)
#define BEAT_25 (BEAT_20 + BEAT_05)
#define BEAT_30 (BEAT_15 * 2)
#define BEAT_35 (BEAT_30 + BEAT_05)
#define BEAT_40 (BEAT_20 * 2)
