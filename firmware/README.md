# Firmware

AVR ATtiny85 firmware written in C using GCC and AVR LibC.

## System Requirements

* avr-binutils
* avr-gcc
* avr-libc
* avrdude

## Quick Start

Configure the project:

```bash
waf configure
```

Build the project:

```bash
waf build
```

Flash the firmware using an AVR ISP Mark 2 USB programmer:

```bash
avrdude -p attiny85 -c avrispmkii -P usb -U flash:w:build/src/snowlite.hex -B1000
```

Note the `-B1000` is necessary for communicating with the ATtiny85 when it's
configured with the default 1 MHz clock. The default speed is too fast and will
fail with random errors regarding unknown device IDs.

## Note Frequencies

Generate note period constants from -7 to 10 half-steps around A4 with a
frequency of 440 Hz given a default 1 MHz CPU clock and 1/16 prescaling:

```bash
./notes.py -p 16 -b 440 --step-low -7 --step-high 10 --header > src/notes.h
```

## References

* [AVR ATtiny85](https://www.microchip.com/wwwproducts/en/ATtiny85)
  * [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)
  * [Fuse Calculator](http://www.engbedded.com/fusecalc/)
* [AVR LibC](http://www.nongnu.org/avr-libc/)
* [AVRDUDE](http://savannah.nongnu.org/projects/avrdude)
* [Waf](https://waf.io/)
* Music
  * [Jingle Bells](https://www.christmasmusicsongs.com/christmas-carol-lyrics-PDFs/jingle-bells-sheet-music-lyrics.pdf)
