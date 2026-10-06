# FasmMacroLib
![GitHub release](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacroLib)
![Language](https://img.shields.io/badge/language%20-%20Assembly-red)
![OS](https://img.shields.io/badge/OS-Linux_FreeBSD_macOS_illumos_9front_Redox--OS_MS--DOS-0078D4)</br>
![CPU](https://img.shields.io/badge/CPU-x86--16_x86--32_x86--64_ARM32_ARM64-orange)
![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacroLib)
![GitHub last commit](https://img.shields.io/github/last-commit/lina-torovoltas/FasmMacrolib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacroLib/total)</br>


Cross-platform FASM macro library for syscalls and common algorithms.</br>


## Usage

### 1. Download the library
Clone the repository to get the macro include files:
```bash
git clone https://github.com/lina-torovoltas/FasmMacroLib
```

### 2. Include in thy code
All macros are located within the `macrolib` directory, structured by OS and architecture folders.</br>
Provide the correct path within thy `.asm` file.</br>
Here are some examples:
```asm
include 'macrolib/Linux/linux_x64.inc'       ; for Linux x86-64
include 'macrolib/Linux/linux_arm64.inc'     ; for Linux ARM64
include 'macrolib/MacOS/macos_arm64.inc'     ; for macOS ARM64
include 'macrolib/FreeBSD/freebsd_x64.inc'   ; for FreeBSD x86-64
include 'macrolib/DOS/dos_x16.inc'           ; for DOS x86-16
```

Practical code snippets, annotated with explanatory comments, may be perused in the [examples](examples) folder.

## Building Examples

Thou canst download pre-built binaries from the [releases](../../releases) section, or compile the source code thyself.</br></br>
For x86 targets thou needest `fasm`, for ARM targets [`fasmarm`](https://arm.flatassembler.net/), and for macOS `clang` and `llvm` in addition.</br>
Ensure that the tools thou needest are installed and available in thy system PATH.</br></br>
Compile the examples using `make`:
```bash
cd FasmMacroLib
make Linux    # Build examples for Linux
make FreeBSD  # Build examples for FreeBSD
make MacOS    # Build examples for macOS
make DOS      # Build examples for DOS
make Illumos  # Build examples for illumos
make 9front   # Build examples for 9front
make Redox    # Build examples for Redox-OS
make all      # Build all supported OS targets at once (requires every tool above)
make clean    # Removes build folder
```

The built binaries shall be found in `build/<target>/examples_<arch>/`.

## Contributing

Contributions are welcome!</br>
If thou hast found a bug or wishest to propose an improvement,</br>
feel free to open an [issue](../../issues) or submit a [pull request](../../pulls).

***
Developed by <a href="https://lina-kiratorasu.codeberg.page/" style="color:#ff4f00">Lina Kiratorasu</a> — © 2025-2026, released under the [MIT License](LICENSE).
