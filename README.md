# FasmMacroLib
![Language](https://img.shields.io/badge/language%20-%20Assembly-red)
![CPU](https://img.shields.io/badge/CPU-x86_x64_x16_ARM-orange)
![OS](https://img.shields.io/badge/OS-Linux_MS--DOS_FreeBSD_MacOS-0078D4)
![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacroLib)
![GitHub last commit](https://img.shields.io/github/last-commit/lina-torovoltas/FasmMacrolib)
![GitHub release](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacroLib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacroLib/total)</br>


FasmMacroLib is a macro library designed to simplify FASM programming upon Linux, MacOS, MS-DOS and FreeBSD.</br>
It supports Linux (x86, x64, ARM, ARM64), MacOS(ARM64), MS-DOS (x16), and FreeBSD (x86, x64).

## Usage

### 1. Download the library
Clone the repository directly to get the macro include files:
```bash
git clone https://github.com/lina-torovoltas/FasmMacroLib
```

### 2. Include in thy code
All macros are located within the `macrolib` directory, structured by OS and architecture folders.</br>
Provide the correct path within thy `.asm` file.</br>
Here are some examples:
```asm
include 'macrolib/LINUX/linux_x64.inc'       ; for Linux x64
include 'macrolib/LINUX/linux_arm64.inc'     ; for Linux ARM64
include 'macrolib/DOS/dos_x16.inc'           ; for DOS x16
include 'macrolib/FreeBSD/freebsd_x64.inc'   ; for FreeBSD x64
```

Full documentation of available macros is provided in [macro_usage.md](macro_usage.md).</br>
Practical code snippets can be perused inside the [examples](examples) folder.

## Building Examples

Thou canst download pre-built binaries from the releases section, or compile the source code thyself.</br>
Ensure that `make`, `fasm`, `llvm`, `clang` and `fasmarm` are installed and available in thy system PATH.</br>
Compile the examples using make:
```bash
cd FasmMacrosLib
make Linux      # Build examples for Linux
make all        # Build all supported OS targets at once
```

## Contributing

Contributions are welcome!</br>
If thou hast found a bug or wishest to propose an improvement,</br>
feel free to open an issue or submit a pull request.

***
Developed by <a href="https://github.com/lina-torovoltas" style="color:#ff4f00">Lina Torovoltas</a> — © 2025-2026 All rights reserved.
