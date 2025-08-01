# Note

Some macros return data in a register.</br>
The specific register used depends on the target architecture:

- x16:    `ax`
- x86:    `eax`  
- x86_64: `rax`  
- ARM32:  `r0`  
- ARM64:  `x0`

Also:  
- For 16-bit targets, only 16-bit unsigned numbers are supported.
- For 32-bit targets, only 32-bit unsigned numbers are supported.
- For 64-bit targets, only 64-bit unsigned numbers are supported.

*Unsigned numbers are non-negative integers (0 and above).*



## Auxiliary Macros

### clr
Clears the specified registers by setting them to zero.

```asm
clr reg1, reg2
```


**Arguments:**</br>
`regN` — actual registers to be cleared (set to zero), depending on the target architecture.


**Usage example:**

```asm
clr ax, bx      ; sets ax and bx to 0
clr eax, ebx    ; sets eax and ebx to 0
clr rax, rdi    ; sets rax and rdi to 0
clr r7, r0      ; sets r7 and r0 to 0
clr x8, x0      ; sets x8 and x0 to 0
```



### push / pop  
Pushes or pops multiple registers on/from the stack (equivalent to multiple `push`/`pop` instructions).</br>
Register order in `pop` must match the reverse of `push`.

```asm
push reg1, reg2, reg3
...
pop reg3, reg2, reg1
```

**Note:**

Not available in the library for FreeBSD(32-bit).


**Arguments:**</br>
`regN` — actual registers to push or pop depending on the target architecture.


**Usage example:**

For x16:
```
push ax, bx, cx
...
pop cx, ax, bx
```

For x86:
```
push eax, edi, esi
...
pop esi, edi, eax
```

For x86_64:
```
push rax, rdi, rsi
...
pop rsi, rdi, rax
```

For ARM:
```
push r0, r1, r2
...
pop r2, r1, r0
```

For ARM64:
```
push x0, x1, x2
...
pop x2, x1, x0
```



### exit
Terminates the program with a specified exit code.

```asm
exit code
```


**Arguments:**</br>
`code` — the exit code to return to the operating system (e.g., `0` for success, `1` for error).


**Usage example:**

```asm
exit 0    ; exit with code 0 
exit 1    ; exit with code 1
```



## Directory Management Macros

### mkdir
Creates a directory with the given name and permissions (in octal format).</br>
Returns an error code in the architecture-specific register.

```asm
mkdir dir_name, permissions
```

**Note:**

Not available in the library for FreeBSD(32-bit).


**Arguments:**</br>
`dir_name` — name of the directory to create, given as a string literal or a pointer to a string.</br>
`permissions` — access mode in octal format, given as a number or a pointer to a variable containing the value. (not required for x16)


**Usage example:**

```asm
mkdir "dir", 700o
mkdir name, permissions
```



### rmdir
Removes the specified directory.</br>
Returns an error code in the architecture-specific register.

```asm
rmdir dir_name
```

**Note:**

Not available in the library for FreeBSD(32-bit).


**Arguments:**</br>
`dir_name` — name of the directory to remove, given as a string literal or a pointer to a string.


**Usage example:**

```asm
rmdir "dir"
rmdir name
```



## Console Output Macros

### print
Prints the string at the given address with the specified length.</br>
Returns the number of bytes printed in the architecture-specific register.

```asm
print str, str_len
```


**Arguments:**  
`str` — pointer to the string or string literal to print.</br>
`str_len` — length of the string in bytes, given as a number or pointer (not required for DOS).


**Usage example:**

```asm
print msg, msg_len
print "test", 4
```



### printtim  
Prints the given string a specified number of times.</br>
Returns the number of bytes printed in the architecture-specific register.

```asm
printtim times, str, str_len
```


**Arguments:**</br>
`times` — number of times to print the string, given as a number or pointer.</br>
`str` — pointer to the string or string literal to print.</br>
`str_len` — length of the string in bytes, given as a number or pointer. (not required for x16)


**Usage example:**

```asm
printtim times, msg, msg_len  
printtim 3, "test", 4
```



### printnum  
Prints the given number in decimal.</br>
Supports values according to the target architecture.</br>
Returns the number of bytes printed in the architecture-specific register.

```asm
printnum number
```

**Note:**

Not available in the library for Linux (ARM 32-bit and ARM 64-bit).


**Arguments:**</br>
`number` — the unsigned integer value to print.


**Usage example:**

```asm
printnum 18446744073709551615
printnum 4294967295
```



## Misc Macros

### time
Stores the current UNIX time (seconds since January 1, 1970) in the architecture-specific register.

```asm
time
```

**Note:**

Not available in the library for DOS, Linux (ARM 32-bit and ARM 64-bit) and FreeBSD(32-bit and 64-bit).



### run
Executes the specified shell command.</br>
Returns an error code in the architecture-specific register.

```asm
run command
```


**Note:**

Not available in the library for DOS, Linux (ARM 32-bit and ARM 64-bit) and FreeBSD(32-bit).


**Arguments:**</br>
`command` — pointer to the command string or a string literal to execute.


**Usage example:**

```
run "echo test"
run cmd_str
```