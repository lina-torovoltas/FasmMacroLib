# FasmMacroLib Documentation

## WARNING
The documentation below is significantly outdated due to a major library update.</br>
To see the latest macro usage examples, please go to the [examples](examples) directory.

## Note

Some macros return data in a register.</br>
The specific register used depends on the target architecture:
- x16: `ax`
- x86 / x86_64: `eax` / `rax`  
- ARM32 / ARM64: `r0` / `x0`

### Platform and Data Restrictions:
- `push` / `pop` - Not available on FreeBSD 32-bit.
- `mkdir` / `rmdir` - Not available on FreeBSD 32-bit.
- `printnum` - Not available on Linux ARM32 and ARM64.
- `time` - Only available on Linux (x86, x64).
- `run` - Only available on Linux (x86, x64) and FreeBSD x64.

Supported number ranges depend on the target architecture:</br>
Up to 2¹⁶-1 for 16-bit, 2³²-1 for 32-bit, and 2⁶⁴-1 for 64-bit (unsigned integers only).


---

## Auxiliary Macros

### clr
Clears the specified registers by setting them to zero.

```asm
clr reg1, reg2
```

`regN` - Actual registers to be cleared, depending on the target architecture.

Example:
```asm
clr ax, bx      ; sets ax and bx to 0
clr eax, ebx    ; sets eax and ebx to 0
clr rax, rdi    ; sets rax and rdi to 0
clr r7, r0      ; sets r7 and r0 to 0
clr x8, x0      ; sets x8 and x0 to 0
```

### push / pop
Pushes or pops multiple registers on/from the stack within a single line. 
The register order in `pop` must strictly be the reverse of `push`.

```asm
push reg1, reg2, reg3
...
pop reg3, reg2, reg1
```
`regN` - Target registers to push or pop.

Example:
```asm
; x16 DOS
push ax, bx, cx
...
pop cx, bx, ax

; x86
push eax, edi, esi
...
pop esi, edi, eax

; x64
push rax, rdi, rsi
...
pop rsi, rdi, rax

; ARM32
push r0, r1, r2
...
pop r2, r1, r0

; ARM64
push x0, x1, x2
...
pop x2, x1, x0
```

### exit
Terminates the program execution and returns control to the operating system.

```asm
exit code
```

`code` - Exit status code (e.g., `0` for success, `1` for error).

Example:
```asm
exit 0    ; exit with success status
exit 1    ; exit with error status
```

---

## Directory Management Macros

### mkdir
Creates a new directory with the specified access permissions.

```asm
mkdir dir_name, permissions
```

`dir_name` - String literal or a pointer to a null-terminated string directory name.</br>
`permissions` - Access mode in octal format (given as a number or variable pointer, not required for x16 DOS).

Example:
```asm
mkdir "dir", 700o
mkdir name, permissions
```

### rmdir
Removes an existing directory from the filesystem.

```asm
rmdir dir_name
```

`dir_name` - String literal or a pointer to a null-terminated string directory name.

Example:
```asm
rmdir "dir"
rmdir name
```

---

## Console Output Macros

### print
Outputs a string of a specified length to the standard output.

```asm
print str, str_len
```
`str` - Pointer to the string or raw string literal to output.</br>
`str_len` - Length of the string in bytes (number or variable pointer, not required for x16 DOS).

Example:
```asm
print msg, msg_len
print "test", 4
```

### printtim
Outputs the specified string a given number of times.

```asm
printtim times, str, str_len
```

`times` - Number of iterations (given as a number or variable pointer).</br>
`str` - Pointer to the string or raw string literal.</br>
`str_len` - String length in bytes (not required for x16 DOS).

Example:
```asm
printtim times, msg, msg_len  
printtim 3, "test", 4
```

### printnum
Prints an unsigned integer value in its decimal representation.

```asm
printnum number
```

`number` - The unsigned integer value or register containing the value to print.

Example:
```asm
printnum 18446744073709551615   ; Max 64-bit value
printnum 4294967295             ; Max 32-bit value
```

---

## Miscellaneous Macros

### time
Retrieves the current UNIX timestamp (seconds elapsed since January 1, 1970).

```asm
time
```

### run
Executes a specified system shell command.

```asm
run command
```

`command` - Pointer to the command string or a raw string literal to execute.

Example:
```asm
run "echo test"
run cmd_str
```

***
Developed by Lina Torovoltas — © 2025-2026 All rights reserved.
