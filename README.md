# arduino_morse_emitter

`arduino_morse_emitter` is an Arduino sketch project that converts input text into a textual Morse code representation and prints the result to the Serial Monitor.

At the current stage, the project focuses on:

- mapping ASCII characters to Morse code patterns,
- decoding Morse symbols from compact 4-bit groups,
- printing `dit` / `dah` sequences to the Serial Monitor,
- providing a clean base for future physical Morse emission with an LED, buzzer, or other output device.

## Current behavior

The sketch currently:

1. defines a Morse dictionary for uppercase and lowercase Latin letters plus space,
2. reads a fixed message stored in the sketch,
3. translates each character into Morse code,
4. writes the Morse representation to the Serial Monitor.

Example message in the current sketch:

```cpp
const char msg_display[] = "Hello world";
```

## Project structure

```text
arduino_morse_emitter/
├── .github/
│   ├── ISSUE_TEMPLATE/
│   ├── workflows/
│   └── PULL_REQUEST_TEMPLATE.md
├── .editorconfig
├── .gitignore
├── CHANGELOG.md
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── LICENSE
├── README.md
├── SECURITY.md
└── arduino_morse_emitter.ino
```

## Requirements

- Arduino IDE 2.x or newer
- a board compatible with the Arduino core API
- Serial Monitor configured to **9600 baud**

The included GitHub Actions workflow is configured to compile the sketch against **Arduino Uno** by default.

## Getting started

### 1. Clone the repository

```bash
git clone https://github.com/<your-username>/arduino_morse_emitter.git
cd arduino_morse_emitter
```

### 2. Open the sketch

Open `arduino_morse_emitter.ino` in Arduino IDE.

### 3. Select board and port

Choose your target board and serial port in Arduino IDE.

### 4. Upload and monitor output

Upload the sketch and open the Serial Monitor at **9600 baud**.

## Notes for future development

This repository is intentionally structured as a small but production-ready open source project. It is ready to grow with:

- LED-based Morse signal output,
- buzzer output,
- configurable words-per-minute timing,
- external message input,
- tests and board matrix compilation.

## License

This repository currently uses the **MIT License**.

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening pull requests.

## Security

Please report vulnerabilities according to [SECURITY.md](SECURITY.md).
