## FasmMacroLib

![Language](https://img.shields.io/badge/language%20-%20Assembler-red)
![CPU](https://img.shields.io/badge/CPU-x86%2C%20x64%2C%20ARM%2C%20ARM64-orange)
![OS](https://img.shields.io/badge/OS-linux-blue)
![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacrosLib)
![GitHub release](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacrosLib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacrosLib/total)</br>
FasmMacroLib is a macro library designed to simplify FASM programming upon Linux.</br>
It supports x86, x86_64, ARM, and ARM64 architectures.

## Installation

Just include the `macrolib` file at the top of thy `.asm` file, depending upon thine architecture:

```asm
include 'macrolib/macrolib_x86.inc'       ; for x86
include 'macrolib/macrolib_x64.inc'       ; for x86_64
include 'macrolib/macrolib_arm.inc'       ; for arm
include 'macrolib/macrolib_arm64.inc'     ; for arm64
```

## Dependencies

- Linux x86, x86_64, ARM or ARM64 operating system  
- `make` utility for building  
- `fasm` assembler for x86 and x86_64 targets
- `fasmarm` assembler for ARM and ARM64 targets

Make sure both `make`, `fasm` and `fasmarm` are installed and available in thy system PATH before building.

## Usage

The list of available macros and their usage is provided in [MACRO_USAGE.md](MACRO_USAGE.md)</br>
For practical examples, peruse the [examples folder](examples).</br>
Built binaries of these examples are available in the [releases](https://github.com/lina-torovoltas/FasmMacrosLib/releases) section.</br>
Alternatively, thou canst build them thyself.

## Building examples

To build examples for a chosen architecture (e.g., x86):
```bash
cd FasmMacroLib
make x86
```

To build examples for all supported architectures at once:
```bash
cd FasmMacroLib
make all
```

## Contributing

Contributions are welcome!</br>
Feel free to open pull requests to improve the library.


## Author

Developed by <a href="https://github.com/lina-torovoltas" style="color:#ff4f00">Lina Torovoltas</a> — © 2025 All rights reserved.
