## Project Structure

```
/
├── .gitignore
├── LICENSE
├── MACROS_USAGE.md
├── Makefile
├── README.md
├── STRUCTURE.md
├── macrolib/
    ├── macrolib_x16.inc
│   ├── macrolib_x86.inc
│   ├── macrolib_x64.inc
│   ├── macrolib_arm.inc
│   └── macrolib_arm64.inc
└── examples/
    ├── examples_x16_com/
    │   ├── clear.asm
    │   ├── exit.asm
    │   ├── make_dir.asm
    │   ├── print_number.asm
    │   ├── print_times.asm
    │   ├── print.asm
    │   ├── remove_dir.asm
    │   └── stackops.asm
    ├── examples_x16_exe/
    │   ├── clear.asm
    │   ├── exit.asm
    │   ├── make_dir.asm
    │   ├── print_number.asm
    │   ├── print_times.asm
    │   ├── print.asm
    │   ├── remove_dir.asm
    │   └── stackops.asm
    ├── examples_x86/
    │   ├── clear.asm
    │   ├── exit.asm
    │   ├── get_time.asm
    │   ├── make_dir.asm
    │   ├── print_number.asm
    │   ├── print_times.asm
    │   ├── print.asm
    │   ├── remove_dir.asm
    │   ├── run_command.asm
    │   └── stackops.asm
    ├── examples_x64/
    │   ├── clear.asm
    │   ├── exit.asm
    │   ├── get_time.asm
    │   ├── make_dir.asm
    │   ├── print_number.asm
    │   ├── print_times.asm
    │   ├── print.asm
    │   ├── remove_dir.asm
    │   ├── run_command.asm
    │   └── stackops.asm
    ├── examples_arm/
    │   ├── clear.asm
    │   ├── exit.asm
    │   ├── make_dir.asm
    │   ├── print_times.asm
    │   ├── print.asm
    │   ├── remove_dir.asm
    │   └── stackops.asm
    └── examples_arm64/
        ├── clear.asm
        ├── exit.asm
        ├── make_dir.asm
        ├── print_times.asm
        ├── print.asm
        ├── remove_dir.asm
        └── stackops.asm
```