## Project Structure

```
/
├── .gitignore
├── LICENSE
├── MACROS_USAGE.md
├── Makefile
├── README.md
├── STRUCTURE.md
├── macrolib
│   ├── BSD
│   │   └── bsd_x64.inc
│   ├── DOS
│   │   └── dos_x16.inc
│   └── Linux
│       ├── linux_arm32.inc
│       ├── linux_arm64.inc
│       ├── linux_x64.inc
│       └── linux_x86.inc
└── examples
    ├── BSD
    │   └── examples_x64
    │       ├── clear.asm
    │       ├── exit.asm
    │       ├── make_dir.asm
    │       ├── print.asm
    │       ├── print_number.asm
    │       ├── print_times.asm
    │       ├── remove_dir.asm
    │       ├── run_command.asm
    │       └── stackops.asm
    ├── DOS
    │   ├── examples_x16_com
    │   │   ├── clear.asm
    │   │   ├── exit.asm
    │   │   ├── make_dir.asm
    │   │   ├── print.asm
    │   │   ├── print_number.asm
    │   │   ├── print_times.asm
    │   │   ├── remove_dir.asm
    │   │   └── stackops.asm
    │   └── examples_x16_exe
    │       ├── clear.asm
    │       ├── exit.asm
    │       ├── make_dir.asm
    │       ├── print.asm
    │       ├── print_number.asm
    │       ├── print_times.asm
    │       ├── remove_dir.asm
    │       └── stackops.asm
    └── Linux
        ├── examples_arm32
        │   ├── clear.asm
        │   ├── exit.asm
        │   ├── make_dir.asm
        │   ├── print.asm
        │   ├── print_times.asm
        │   ├── remove_dir.asm
        │   └── stackops.asm
        ├── examples_arm64
        │   ├── clear.asm
        │   ├── exit.asm
        │   ├── make_dir.asm
        │   ├── print.asm
        │   ├── print_times.asm
        │   ├── remove_dir.asm
        │   └── stackops.asm
        ├── examples_x64
        │   ├── clear.asm
        │   ├── exit.asm
        │   ├── get_time.asm
        │   ├── make_dir.asm
        │   ├── print.asm
        │   ├── print_number.asm
        │   ├── print_times.asm
        │   ├── remove_dir.asm
        │   ├── run_command.asm
        │   └── stackops.asm
        └── examples_x86
            ├── clear.asm
            ├── exit.asm
            ├── get_time.asm
            ├── make_dir.asm
            ├── print.asm
            ├── print_number.asm
            ├── print_times.asm
            ├── remove_dir.asm
            ├── run_command.asm
            └── stackops.asm
```