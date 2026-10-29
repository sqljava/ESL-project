# nRF52840 Blinky — Workshop 2

Embedded Systems Lab — Workshop 2

## Hardware
- Nordic nRF52840 Dongle (PCA10059)
- ARM Cortex-M4

## Description
Modified Nordic SDK Blinky example to blink LEDs according to device ID **#7207**.

| LED | Color | Blink count |
|---|---|---|
| 0 | Yellow/green (separate LED) | 7 |
| 1 | Red (RGB) | 2 |
| 2 | Green (RGB) | 0 |
| 3 | Blue (RGB) | 7 |

Each blink uses 200 ms ON and 200 ms OFF, with an 800 ms pause between LED stages.

## Dependencies
- [ESL Nordic SDK](https://github.com/DSRCorporation/esl-nsdk)
- ARM GNU Toolchain
- GNU Make
- nrfutil 6.1.3 for USB DFU flashing

## Build

Clone the ESL Nordic SDK separately and specify its location:

```bash
make SDK_ROOT=/path/to/esl-nsdk
```

## Flash

Put the PCA10059 into DFU bootloader mode, then run:

```bash
make dfu SDK_ROOT=/path/to/esl-nsdk
```

The project uses an external Nordic SDK and does not include the SDK source code.