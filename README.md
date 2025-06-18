## FasmMacroLib

![License](https://img.shields.io/github/license/lina-torovoltas/FasmMacrosLib)
![Version](https://img.shields.io/github/v/release/lina-torovoltas/FasmMacrosLib)
![Downloads](https://img.shields.io/github/downloads/lina-torovoltas/FasmMacrosLib/total)</br>
FasmMacrosLib is a macro library for simplifying FASM programming on 64-bit Linux.


## Dependencies

Works only on Linux x86_64 (64-bit).


## Installation

Just include the macros file at the beginning of your .asm file:

```asm
include 'macroslib.inc'
```


## Usage

Below is a detailed list of available macros and their usage.</br>
For practical examples, see [examples folder](macroslib/examples).</br>
Compiled binaries of these examples are available in the [releases](https://github.com/lina-torovoltas/FasmMacrosLib/releases) section.

### clr
Clears the specified register (sets it to zero).

```asm
clr rax
```

### exit
Terminates the program with a specified exit code.

```asm
exit 0         ; exit with code 0
exit 1         ; exit with code 1
```

### time
Stores the current time (seconds since January 1, 1970) in register rax.

```asm
time
```

### mkdir
Creates a directory with the given name and permissions (octal format).</br>
Returns error code in rax.

```asm
mkdir "test", 777o
```

### rmdir
Removes the specified directory.</br>
Returns error code in rax.

```asm
rmdir "test"
```

### printnum
Prints the given number in decimal.</br>
Returns the number of bytes printed in rax.

```asm
printnum 244939252
```

### print
Prints the string at the given address with the specified length.</br>
Returns the number of bytes printed in rax.

```asm
print "test", 4
```

### printtim
Prints the given string a specified number of times.</br>
Returns the number of bytes printed in rax.

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
push rax, rdi, rsi, rdx
...
pop rdx, rsi, rdi, rax
```


## Contributing

Contributions are welcome!</br>
Feel free to open pull requests to improve the library.


## Author

Developed by <a href="https://github.com/lina-torovoltas" style="color:#ff4f00">Lina Torovoltas</a> — © 2025 All rights reserved.