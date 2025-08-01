DIRS_LINUX = examples_arm32 examples_arm64 examples_x64 examples_x86
DIRS_FREEBSD = examples_x64 examples_x86
DIRS_DOS = examples_x16_com examples_x16_exe

ASM_LINUX_X64   = $(wildcard examples/Linux/examples_x64/*.asm)
ASM_LINUX_X86   = $(wildcard examples/Linux/examples_x86/*.asm)
ASM_LINUX_ARM32 = $(wildcard examples/Linux/examples_arm32/*.asm)
ASM_LINUX_ARM64 = $(wildcard examples/Linux/examples_arm64/*.asm)
ASM_FREEBSD_X64 = $(wildcard examples/FreeBSD/examples_x64/*.asm)
ASM_FREEBSD_X86 = $(wildcard examples/FreeBSD/examples_x86/*.asm)
ASM_DOS_COM = $(wildcard examples/DOS/examples_x16_com/*.asm)
ASM_DOS_EXE = $(wildcard examples/DOS/examples_x16_exe/*.asm)


Linux:
	@for dir in $(DIRS_LINUX); do \
		mkdir -p build/Linux/$$dir >/dev/null 2>&1; \
	done
	@for src in $(ASM_LINUX_X64); do \
		dst=build/Linux/$${src#examples/Linux/}; \
		dst=$${dst%.asm}; \
		fasm $$src $$dst; \
	done
	@for src in $(ASM_LINUX_X86); do \
		dst=build/Linux/$${src#examples/Linux/}; \
		dst=$${dst%.asm}; \
		fasm $$src $$dst; \
	done
	@for src in $(ASM_LINUX_ARM32); do \
		dst=build/Linux/$${src#examples/Linux/}; \
		dst=$${dst%.asm}; \
		fasmarm $$src $$dst; \
	done
	@for src in $(ASM_LINUX_ARM64); do \
		dst=build/Linux/$${src#examples/Linux/}; \
		dst=$${dst%.asm}; \
		fasmarm $$src $$dst; \
	done

FreeBSD:
	@for dir in $(DIRS_FREEBSD); do \
		mkdir -p build/FreeBSD/$$dir >/dev/null 2>&1; \
	done
	@for src in $(ASM_FREEBSD_X64); do \
		dst=build/FreeBSD/$${src#examples/FreeBSD/}; \
		dst=$${dst%.asm}; \
		fasm $$src $$dst; \
	done
	@for src in $(ASM_FREEBSD_X86); do \
		dst=build/FreeBSD/$${src#examples/FreeBSD/}; \
		dst=$${dst%.asm}; \
		fasm $$src $$dst; \
	done

DOS:
	@for dir in $(DIRS_DOS); do \
		mkdir -p build/DOS/$$dir >/dev/null 2>&1; \
	done
	@for src in $(ASM_DOS_COM); do \
		dst=build/DOS/$${src#examples/DOS/}; \
		dst=$${dst%.asm}.com; \
		fasm $$src $$dst; \
	done
	@for src in $(ASM_DOS_EXE); do \
		dst=build/DOS/$${src#examples/DOS/}; \
		dst=$${dst%.asm}.exe; \
		fasm $$src $$dst; \
	done

all: Linux FreeBSD DOS

clean:
	@rm -rf build