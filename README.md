## FasmMacroLib

![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacrosLib)
![Version](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacrosLib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacrosLib/total)</br>
FasmMacroLib is a macro library for simplifying FASM programming upon both 32-bit and 64-bit Linux architectures.

## Dependencies

- Linux x86 (32-bit) or x86_64 (64-bit) operating system  
- `make` utility for building  
- `fasm` assembler for compiling the assembly code

Make sure both `make` and `fasm` are installed and available in thy system PATH before building.


## Installation

Just include the macros file at the fore of thy .asm file, according to thine architecture:

```asm
include 'macrolib_x86/macrolib.inc'       ; for 32-bit x86
include 'macrolib_x86_64/macrolib.inc'    ; for 64-bit x86_64
```


## Usage

Below is a detailed list of available macros and their usage.</br>
For practical examples, peruse the [x86 examples folder](macrolib_x86/examples) or the [x86_64 examples folder](macrolib_x86_64/examples).</br>
Compiled binaries of these examples are available in the [releases](https://github.com/lina-torovoltas/FasmMacrosLib/releases) section.</br>
Alternatively, thou canst compile them thyself.

To build for a chosen architecture (e.g., x86):
```bash
cd FasmMacroLib
make x86
```

To build for all supported architectures at once:
```bash
cd FasmMacroLib
make all
```

### clr
Clears the specified register (sets it to zero).

```asm
; 64-bit
clr rax

; 32-bit
clr eax
```

### exit
Terminates the program with a specified exit code.

```asm
exit 0         ; exit with code 0
exit 1         ; exit with code 1
```

### time
Stores the current time (seconds since January 1, 1970) in register rax/eax.

```asm
time
```

### mkdir
Creates a directory with the given name and permissions (octal format).</br>
Returns error code in rax/eax.

```asm
mkdir "test", 777o
```

### rmdir
Removes the specified directory.</br>
Returns error code in rax/eax.

```asm
rmdir "test"
```

### printnum
Prints the given number in decimal.</br>
Supports values from 0 to 4,294,967,295 (32-bit) and up to 18,446,744,073,709,551,615 (64-bit).</br>
Returns the number of bytes printed in rax/eax.

```asm
; 64-bit
printnum 18446744073709551615

; 32-bit
printnum 4294967295
```

### print
Prints the string at the given address with the specified length.</br>
Returns the number of bytes printed in rax/eax.

```asm
print "test", 4
```

### printtim
Prints the given string a specified number of times.</br>
Returns the number of bytes printed in rax/eax.

```asm
printtim 2, "test", 4
```

### run
Executes the specified shell command.

```asm
run "echo test"
```

### push / pop
Pushes or pops multiple registers on/from the stack (like multiple push/pop instructions combined).

```asm
; 64-bit
push rax, rdi, rsi, rdx
...
pop rdx, rsi, rdi, rax

; 32-bit
push eax, edi, esi, edx
...
pop edx, esi, edi, eax
```


## Contributing

Contributions are welcome!</br>
Feel free to open pull requests to improve the library.


## Author

Developed by <a href="https://github.com/lina-torovoltas" style="color:#ff4f00">Lina Torovoltas</a> — © 2025 All rights reserved.