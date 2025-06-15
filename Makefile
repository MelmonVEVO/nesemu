CC := gcc
TARGET := MelNES

SRC_DIR := ./src
INC_DIR := ./include
BUILD_DIR := ./out

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

CFLAGS := -I$(INC_DIR) -Wall -Wextra -MMD -MP
LDFLAGS :=

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

# Tests

UNITY_SRC_DIR := ./unity/src
UNITY_SRC := $(wildcard $(UNITY_SRC_DIR)/*.c)
UNITY_OBJ := $(patsubst $(UNITY_SRC_DIR)/%.c, $(BUILD_DIR)/unity_%.o,$(UNITY_SRC))

TEST_DIR := ./test
TEST_SRC     := $(wildcard $(TEST_DIR)/*.test.c)
TEST_BIN     := $(patsubst $(TEST_DIR)/%.test.c,$(BUILD_DIR)/%_test,$(TEST_SRC))
RESULT_DIR := ./out/results

TEST_CFLAGS := -I./unity/src
TEST_RESULTS := $(patsubst $(BUILD_DIR)/%_test,$(RESULT_DIR)/%.txt,$(TEST_BIN))

$(RESULT_DIR):
	@mkdir -p $@

$(BUILD_DIR)/unity_%.o: $(UNITY_SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%.test.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_test: $(BUILD_DIR)/%.o $(UNITY_OBJ) $(BUILD_DIR)/%_test.o | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

$(RESULT_DIR)/%.txt: $(BUILD_DIR)/%_test | $(RESULT_DIR)
	-./$< > $@ 2>&1

test: $(TEST_RESULTS)
	@echo "================== TEST SUITE RESULTS =================="
	@echo "----------------------- IGNORED: -----------------------"
	@echo "$$(grep -h :IGNORE $(RESULT_DIR)/*.txt | wc -l)"
	@echo "------------------------ FAILED: -----------------------"
	@echo "$$(grep -h :FAIL   $(RESULT_DIR)/*.txt | wc -l)"
	@echo "------------------------ PASSED: -----------------------"
	@echo "$$(grep -h :PASS   $(RESULT_DIR)/*.txt | wc -l)"
	@failed=$$(grep -h :FAIL: $(RESULT_DIR)/*.txt); \
	if [ -n "$$failed" ]; then \
		echo "=============== SUMMARY OF FAILED TESTS ================"; \
		echo "$$failed"; \
		echo ""; \
	  echo "========================================================" ; \
		exit 1; \
	fi
	@echo "======================== ALL OK ========================"

