SRC_x16_com = examples/examples_x16_com
SRC_x16_exe = examples/examples_x16_exe
SRC_x86 = examples/examples_x86
SRC_x64 = examples/examples_x64
SRC_arm32 = examples/examples_arm32
SRC_arm64 = examples/examples_arm64

BUILD_DIR = build
BUILD_x16_com = $(BUILD_DIR)/examples_x16_com
BUILD_x16_exe = $(BUILD_DIR)/examples_x16_exe
BUILD_x86 = $(BUILD_DIR)/examples_x86
BUILD_x64 = $(BUILD_DIR)/examples_x64
BUILD_arm32 = $(BUILD_DIR)/examples_arm32
BUILD_arm64 = $(BUILD_DIR)/examples_arm64

FASM = fasm
FASMA = fasmarm

all: x16_com x16_exe x86 x64 arm32 arm64
.PHONY: x16_com x16_exe x86 x64 arm32 arm64 all clean check_tools check_dirs

check_tools:
	@command -v $(FASM) >/dev/null 2>&1 || { echo "Error: $(FASM) is not installed or not in PATH"; exit 1; }
	@command -v $(FASMA) >/dev/null 2>&1 || { echo "Error: $(FASMA) is not installed or not in PATH"; exit 1; }

check_dirs:
	@for dir in $(SRC_x16_com) $(SRC_x16_exe) $(SRC_x86) $(SRC_x64) $(SRC_arm32) $(SRC_arm64); do \
		if [ ! -d $$dir ]; then \
			echo "Error: Source directory '$$dir' does not exist"; exit 1; \
		fi \
	done

x16_com: check_tools check_dirs
	@mkdir -p $(BUILD_x16_com)
	@for file in $(SRC_x16_com)/*.asm; do \
		base=$$(basename $$file .asm); \
		output="$(BUILD_x16_com)/$$base.com"; \
		echo "Building $$file -> $$output"; \
		$(FASM) "$$file" "$$output" || exit 1; \
	done

x16_exe: check_tools check_dirs
	@mkdir -p $(BUILD_x16_exe)
	@for file in $(SRC_x16_exe)/*.asm; do \
		base=$$(basename $$file .asm); \
		output="$(BUILD_x16_exe)/$$base.exe"; \
		echo "Building $$file -> $$output"; \
		$(FASM) "$$file" "$$output" || exit 1; \
	done

x86: check_tools check_dirs
	@mkdir -p $(BUILD_x86)
	@for file in $(SRC_x86)/*.asm; do \
		output=$(BUILD_x86)/$$(basename $$file .asm); \
		echo "Building $$file -> $$output"; \
		$(FASM) $$file $$output || exit 1; \
	done

x64: check_tools check_dirs
	@mkdir -p $(BUILD_x64)
	@for file in $(SRC_x64)/*.asm; do \
		output=$(BUILD_x64)/$$(basename $$file .asm); \
		echo "Building $$file -> $$output"; \
		$(FASM) $$file $$output || exit 1; \
	done

arm32: check_tools check_dirs
	@mkdir -p $(BUILD_arm32)
	@for file in $(SRC_arm32)/*.asm; do \
		output=$(BUILD_arm32)/$$(basename $$file .asm); \
		echo "Building $$file -> $$output"; \
		$(FASMA) $$file $$output || exit 1; \
	done

arm64: check_tools check_dirs
	@mkdir -p $(BUILD_arm64)
	@for file in $(SRC_arm64)/*.asm; do \
		output=$(BUILD_arm64)/$$(basename $$file .asm); \
		echo "Building $$file -> $$output"; \
		$(FASMA) $$file $$output || exit 1; \
	done

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directories"