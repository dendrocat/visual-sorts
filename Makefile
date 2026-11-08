DIR        = src
BUILD_DIR  = build
SOURCES    = $(DIR)/test.cpp \
             $(DIR)/model/VectorModel.cpp \
             $(DIR)/model/SyncGate.cpp \
             $(DIR)/model/SyncingModel.cpp

CXX        = g++
CXXFLAGS   = -std=c++23 -pedantic-errors -Werror -Wall -Wextra -pthread -I$(DIR)

TARGET  = $(BUILD_DIR)/test
MKDIR   = mkdir -p "$(BUILD_DIR)"
RM      = rm -f
RUN     = ./$(TARGET)
CLEAN 	= rm -f $(TARGET)

all: run
clean_build: clean run

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

run: $(TARGET)
	@echo ======Running $(TARGET)======
	@$(RUN)

clean:
	@echo ======Removing $(TARGET)======
	@$(CLEAN)

.PHONY: all build run clean
