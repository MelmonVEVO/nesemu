CC := gcc
TARGET := MelNES

SRC_DIR := ./src
INC_DIR := ./include
BUILD_DIR := ./out

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

CFLAGS := -I$(INC_DIR) -Wall -Wextra -MMD -MP
LDFLAGS :=

TEST_DIR := ./test
TEST_BUILD_DIR := $(BUILD_DIR)/test
TEST_TARGET := $(TEST_BUILD_DIR)/test_runner

ifeq ($(DEBUG), 1)
	CFLAGS += -g -Og -DDEBUG
else
	CFLAGS += -O2 -DRELEASE
endif

.PHONY: all clean debug test

all: $(BUILD_DIR)/$(TARGET)

# Link object files and create the binary.
$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile object files from .c files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

debug:
	$(MAKE) DEBUG=1

clean:
	rm -r $(BUILD_DIR)

-include $(DEP)

test: $(TEST_TARGET)
	echo "Running unit tests:"

# TODO: test things

