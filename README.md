# Embedded Systems Lab — Workshop 4 (nRF52840 PCA10059)

Device ID **7207**. This is a stand-alone source project built against the course's external `esl-nsdk`.

## Required features

- PWM0 hardware output runs at **1 kHz** (1 MHz clock / COUNTERTOP 1000).
- 201 levels form each brightness fade: 0 → 100 → 0 percent; levels advance every 10 ms (about 2 seconds per fade).
- Sequence order: **7 yellow**, **2 red**, **0 green**, **7 blue**; 800 ms between color groups.
- SW1 on P1.06 is handled by the **GPIOTE interrupt**, using a pull-up and software debounce (30 ms).
- Two press/release clicks completed within about **300 ms** start or freeze the sequence. A second double-click resumes from the same position and brightness.
- All four PWM outputs remain active while progression is frozen; the current duty cycle is maintained.

## Modules

| Module | Responsibility |
|---|---|
| `main.c` | Initializes peripherals and schedules a 10 ms foreground update |
| `src/led.c` | Creates PWM data in RAM, configures and steps PWM0 |
| `src/button.c` | SW1 GPIOTE edges, 30 ms debounce, double-click detection |
| `src/sequence.c` | Maintains running/paused state and advances PWM |
| `config/sdk_config.h` | SDK driver feature flags |

## Build and flash

With the `esl-nsdk` installed at `~/devel/esl-nsdk`:

```sh
make
```

Put dongle in USB DFU mode (red pulsing bootloader LED):

```sh
make dfu
```

Do not run `make dfu` until the build succeeds and you have checked that the local USB port is correct (`DFU_PORT` defaults to `/dev/ttyACM0`).

## Known tradeoffs

- The foreground update uses a blocking **10 ms delay** for simplicity. GPIOTE still handles button transitions with interrupts; the main loop does not poll the input pin.
- Timing has normal 10 ms quantization and oscillator/instruction overhead. This is adequate for the course exercise but not a precision real-time scheduler.
- The first click is recognized when the button is released; the double-click toggle is recognized at the second release.
- USB logging is the *optional* part of the assignment and has not been included.

## Hardware test checklist

1. Boot with no button press: LEDs OFF.
2. One click: no change.
3. Two clicks within 300 ms: fade sequence begins.
4. Confirm yellow ×7, red ×2, green ×0, blue ×7, repeating.
5. Double-click while LED is partially bright: it stays at the same brightness.
6. Double-click again: brightness continues from the frozen value.
7. Check that a slow pair of clicks does not toggle and that contact bounce is not counted as extra clicks.

## Integration caveat

The source was prepared from the GitHub `workshop-4` branch. Before submitting, build it with your exact course SDK/toolchain and check the observed behavior on a physical PCA10059. The firmware is not asserted to be hardware-verified merely because source code is included here.
