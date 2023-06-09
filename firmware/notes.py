#!/usr/bin/env python

import string
import argparse
from collections import namedtuple

from colored import fg, attr
from beautifultable import BeautifulTable


Note = namedtuple('Note', ['octave', 'half_step', 'frequency', 'counts'])

NOTE_NAMES = [
    'C',
    'C#/Db',
    'D',
    'D#/Eb',
    'E',
    'F',
    'F#/Gb',
    'G',
    'G#/Ab',
    'A',
    'A#/Bb',
    'B'
]

NOTE_SYMBOLS = [
    'C',
    'CS',
    'D',
    'DS',
    'E',
    'F',
    'FS',
    'G',
    'GS',
    'A',
    'AS',
    'B'
]


def generate_notes(clock_base, prescaling, step_low, step_high, note_base):
    """
    Generate note frequencies from a base note (A4) frequency and determine
    how many counts at the scaled timer clock are necessary to represent them.

    https://pages.mtu.edu/~suits/NoteFreqCalcs.html
    https://pages.mtu.edu/~suits/notefreqs.html
    """

    clock_scaled = clock_base / prescaling
    twelth_root = pow(2.0, 1.0 / 12.0) # a constant
    lowest_step = -((4 * 12) + 9) # A4 = C0 + (4 octaves * 12 notes) + 9 half steps
    highest_step = (4 * 12) + 3 # B8 = A4 + (4 octaves * 12 notes) + 3 half steps

    if step_low < lowest_step:
        raise ValueError(f"step_low {step_low} below minimum {lowest_step}")

    if step_high > highest_step:
        raise ValueError(f"step_high {step_high} above maximum {highest_step}")

    notes = []
    for offset_step in range(step_low, step_high):
        octave, half_step = divmod(offset_step - lowest_step, 12)
        frequency = round(note_base * pow(twelth_root, offset_step), 2)
        counts = round(clock_scaled / frequency)

        notes.append(Note(octave, half_step, frequency, counts))

    return notes


def display_table(notes):
    """
    Display a list of notes in a table.
    """

    table = BeautifulTable(max_width=120)
    table.column_headers = ["Octave", "Half Step", "Name", "Frequency", "Counts"]

    for note in notes:
        if note.counts < 1 or note.counts >= 255:
            counts = "{}{}{}".format(fg('red'), note.counts, attr('reset'))

        else:
            counts = str(note.counts)

        table.append_row([
            note.octave,
            note.half_step,
            NOTE_NAMES[note.half_step],
            note.frequency,
            counts])

    print(table)


def display_header(notes):
    """
    Display a C header file with defines for the notes.
    """

    def format_symbol(note):
        return "\n// {} {} ({} Hz)\n#define NOTE_{}{} {}".format(
            NOTE_NAMES[note.half_step],
            note.octave,
            note.frequency,
            NOTE_SYMBOLS[note.half_step],
            note.octave,
            note.counts)

    notes = list(filter(lambda n: n.counts > 0 and n.counts < 255, notes))
    symbols = "\n".join(map(format_symbol, notes))

    print("#pragma once")
    print("\n// Rest Magic Value\n#define NOTE_REST 0")
    print(symbols)


def main():
    """
    Run the console interface.
    """

    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-c', '--clock',
        type=int,
        default=(1024 * 1024),
        help="Clock Frequency (Hz)")

    parser.add_argument(
        '-p', '--prescaling',
        type=int,
        required=True,
        help="Prescaler Divisor")

    parser.add_argument(
        '--step-low',
        default=-9,
        type=int,
        help="Low Half Step")

    parser.add_argument(
        '--step-high',
        default=5,
        type=int,
        help="High Half Step")

    parser.add_argument(
        '-b', '--base',
        type=int,
        required=True,
        help="Base Frequency (Hz)")

    parser.add_argument(
        '--header',
        action='store_true',
        help="generate header file")

    args = parser.parse_args()
    notes = generate_notes(
        args.clock,
        args.prescaling,
        args.step_low,
        args.step_high,
        args.base)

    if args.header:
        display_header(notes)

    else:
        display_table(notes)


if __name__ == '__main__':
    main()
