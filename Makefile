FASM = fasm

# Пути исходников
SRC_x86 = macrolib_x86/examples
SRC_x86_64 = macrolib_x86_64/examples
SRC_arm32 = macrolib_arm32/examples
SRC_arm64 = macrolib_arm64/examples

# Папки сборки
BUILD_x86 = build_x86
BUILD_x86_64 = build_x86_64
BUILD_arm32 = build_arm32
BUILD_arm64 = build_arm64

.PHONY: all clean x86 x86_64 arm32 arm64

all: x86 x86_64 arm32 arm64

x86:
	@echo "Building x86..."
	@mkdir -p $(BUILD_x86)
	@for file in $(SRC_x86)/*.asm; do \
		output=$(BUILD_x86)/$$(basename $$file .asm); \
		$(FASM) $$file $$output || exit 1; \
	done
	@echo "x86 build done."

x86_64:
	@echo "Building x86_64..."
	@mkdir -p $(BUILD_x86_64)
	@for file in $(SRC_x86_64)/*.asm; do \
		output=$(BUILD_x86_64)/$$(basename $$file .asm); \
		$(FASM) $$file $$output || exit 1; \
	done
	@echo "x86_64 build done."

arm32:
	@echo "Building arm32..."
	@mkdir -p $(BUILD_arm32)
	@for file in $(SRC_arm32)/*.asm; do \
		output=$(BUILD_arm32)/$$(basename $$file .asm); \
		$(FASM) $$file $$output || exit 1; \
	done
	@echo "arm32 build done."

arm64:
	@echo "Building arm64..."
	@mkdir -p $(BUILD_arm64)
	@for file in $(SRC_arm64)/*.asm; do \
		output=$(BUILD_arm64)/$$(basename $$file .asm); \
		$(FASM) $$file $$output || exit 1; \
	done
	@echo "arm64 build done."

clean:
	@echo "Cleaning build directories..."
	@rm -rf $(BUILD_x86) $(BUILD_x86_64) $(BUILD_arm32) $(BUILD_arm64)
	@echo "Clean done."