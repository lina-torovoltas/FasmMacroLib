# FasmMacrosLib
Macros library for FASM (Flat Assembler) for Linux

## Installation

Just include the macros file at the beginning of your .asm file:

```asm
include 'macroslib.inc'
```

## Macros

### clr
Clears the specified register (sets it to zero).

Usage:
```asm
clr rax
```

### exit
Terminates the program with a specified exit code.

Usage:
```asm
exit 0         ; exit with code 0
exit 1         ; exit with code 1
```

### time
Stores the current time (seconds since January 1, 1970) in register rax.

Usage:
```asm
time
; rax now contains the Unix timestamp
```


### mkdir
Creates a directory with the given name and permissions (e.g., 777o for octal 0777).  
Returns error code in rax.

Usage:
```asm
mkdir name, 777o
```


### rmdir
Removes the specified directory.  
Returns error code in rax.

Usage:
```asm
rmdir name
```

### printnum
Prints the given number in decimal.  
Returns the number of bytes printed in rax.

Usage:
```asm
printnum 1234
```


### print
Prints the string at the given address with the specified length.  
Returns the number of bytes printed in rax.

Usage:
```asm
print msg, msg_len
```


### printtim
Prints the given string a specified number of times.  
Returns the total number of bytes printed in rax.

Usage:
```asm
printtim 2, msg, msg_len
```


### run
Executes the specified shell command.

Usage:
```asm
run "echo Hello"
```


### push / pop
Pushes or pops multiple registers on/from the stack (like multiple push/pop instructions combined).

Usage:
```asm
push rax, rdi, rsi, rdx
...
pop rdx, rsi, rdi, rax
```


## Dependencies

Works only on Linux x86_64.
