SRC_DIR := macrolib/examples
BUILD_DIR := build

ASM_SOURCES := $(wildcard $(SRC_DIR)/*.asm)

BINARIES := $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%, $(ASM_SOURCES))

all: $(BUILD_DIR) $(BINARIES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	fasm $< $@

clean:
	rm -rf $(BUILD_DIR)
