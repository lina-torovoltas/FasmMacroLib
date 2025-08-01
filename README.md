## FasmMacroLib

![Language](https://img.shields.io/badge/language%20-%20Assembly-red)
![CPU](https://img.shields.io/badge/CPU-x16%2C%20x86%2C%20x64%2C%20ARM32%2C%20ARM64-orange)
![OS](https://img.shields.io/badge/OS-Linux%2C%20DOS%2C%20FreeBSD-0078D4)
![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacrosLib)
![GitHub release](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacrosLib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacrosLib/total)</br>
FasmMacroLib is a macro library designed to simplify FASM programming upon Linux, DOS and BSD.</br>
It supports Linux (x86, x64, ARM, ARM64), DOS (x16), and FreeBSD (x86, x64).

## Installation

Just include the macrolib file at the top of thy .asm file, depending upon thine OS and architecture:

```asm
include 'linux_x86.inc'       ; for Linux x86
include 'linux_x64.inc'       ; for Linux x64
include 'linux_arm32.inc'     ; for Linux arm32
include 'linux_arm64.inc'     ; for Linux arm64
include 'dos_x16.inc'         ; for DOS x16
include 'freebsd_x86.inc'         ; for FreeBSD x86
include 'freebsd_x64.inc'         ; for FreeBSD x64
```

## Dependencies

- `make` utility for building
- `fasm` assembler for x16, x86 and x64 targets
- `fasmarm` assembler for ARM32 and ARM64 targets

Make sure both `make`, `fasm` and `fasmarm` are installed and available in thy system PATH before building.

## Usage

The list of available macros and their usage is provided in [MACRO_USAGE.md](MACRO_USAGE.md)</br>
For practical examples, peruse the [examples folder](examples).</br>
Built binaries of these examples are available in the [releases](https://github.com/lina-torovoltas/FasmMacrosLib/releases) section.</br>
Alternatively, thou canst build them thyself.

## Building examples

To build examples for a chosen operating system (e.g., Linux):
```bash
cd FasmMacroLib
make Linux
```

To build examples for all supported operating systems at once:
```bash
cd FasmMacroLib
make all
```

## Contributing

Contributions are welcome!</br>
Feel free to open pull requests to improve the library.


## Author

Developed by <a href="https://github.com/lina-torovoltas" style="color:#ff4f00">Lina Torovoltas</a> — © 2025 All rights reserved.
