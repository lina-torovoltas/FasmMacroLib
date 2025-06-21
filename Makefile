SRC_x86 = examples/examples_x86
SRC_x64 = examples/examples_x64
SRC_arm = examples/examples_arm
SRC_arm64 = examples/examples_arm64

BUILD_DIR = build
BUILD_x86 = $(BUILD_DIR)/examples_x86
BUILD_x64 = $(BUILD_DIR)/examples_x64
BUILD_arm = $(BUILD_DIR)/examples_arm
BUILD_arm64 = $(BUILD_DIR)/examples_arm64

# Assemblers
FASM = fasm
FASMA = fasmarm

.PHONY: x86 x64 arm arm64 all clean check_tools check_dirs

# Check if tools exist
check_tools:
	@command -v $(FASM) >/dev/null 2>&1 || { echo "Error: $(FASM) is not installed or not in PATH"; exit 1; }
	@command -v $(FASMA) >/dev/null 2>&1 || { echo "Error: $(FASMA) is not installed or not in PATH"; exit 1; }

# Check if source directories exist
check_dirs:
	@for dir in $(SRC_x86) $(SRC_x64) $(SRC_arm) $(SRC_arm64); do \
		if [ ! -d $$dir ]; then \
			echo "Error: Source directory '$$dir' does not exist"; exit 1; \
		fi \
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

arm: check_tools check_dirs
	@mkdir -p $(BUILD_arm)
	@for file in $(SRC_arm)/*.asm; do \
		output=$(BUILD_arm)/$$(basename $$file .asm); \
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

all: x86 x64 arm arm64

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directories"