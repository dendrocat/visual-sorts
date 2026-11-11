.PHONY: debug release test clean
.DEFAULT_GOAL := help

CONFIGURE = cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
BUILD_DIR = build
DEBUG_DIR = debug
RELEASE_DIR = debug

BUILD_DEBUG = $(BUILD_DIR)/$(DEBUG_DIR)
BUILD_RELEASE = $(BUILD_DIR)/$(RELEASE_DIR)

help:
	@echo "usage: make <target>"
	@echo ""
	@echo "  debug     build & run (Debug)"
	@echo "  release   build & run (Release)"
	@echo "  test      build & run tests"
	@echo "  clean     remove build/"

debug:
	$(CONFIGURE)
	cmake --build $(BUILD_DEBUG) --target main
	@ln -sf $(DEBUG_DIR)/compile_commands.json $(BUILD_DIR)/compile_commands.json
	./$(BUILD_DEBUG)/main

release:
	cmake -S . -B $(BUILD_RELEASE) -G Ninja -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_RELEASE) --target main
	@ln -sf $(RELEASE_DIR)/compile_commands.json $(BUILD_DIR)/compile_commands.json
	./$(BUILD_RELEASE)/main

test:
	$(CONFIGURE)
	cmake --build $(BUILD_DEBUG) --target test
	@ln -sf $(DEBUG_DIR)/compile_commands.json $(BUILD_DIR)/compile_commands.json
	./$(BUILD_DEBUG)/main

clean:
	rm -rf $(BUILD_DIR)
