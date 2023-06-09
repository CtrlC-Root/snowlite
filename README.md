# snowlite


* `circuit`: KiCad circuit schematic.
* `firmware`: AVR ATtiny85 firmware.
* `models`: OpenSCAD models for the case and logo.

## Project Setup

Create a Python virtual environment and install script requirements:

```bash
python -m venv env
pip install -r requirements.txt
```

Append the local tools directory to your `PATH` variable:

```bash
export PATH="$PATH:$(pwd)/tools"
```
