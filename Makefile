## PROJECT SETTINGS ##


# Project name
PROJECT_NAME := CUTE


# Project directories
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test


# Documentation
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc


# Installation directory
INST_DIR := /usr/local



## BUILD SETTINGS ##


# Debugging
# y/n
DEBUG := n

# Optimization level at compilation (0 => no optimization)
# 0..3/s
OPTIM_LVL := 2



## VARIABLES ##


# Test executable
TEST_EXEC := test_$(PROJECT_NAME)

# Tests files
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/test_%.o,$(TEST_SRC))
TEST_LOG := test.log

# Project sources and object files
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Library archive
AR_LIB := lib$(PROJECT_NAME).a


# Preprocessor flags
CPPFLAGS := -I$(INC_DIR) -D_POSIX_C_SOURCE=200809L
# Compilation flags
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded -O$(OPTIM_LVL)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif

# The libraries to link against
LDLIBS := -lclog

# Linkage flags
LDFLAGS := -L.



## RULES ##

# All rule names that do not refer to a file
.PHONY: all clean distclean doc test testclean

# The default rule to execute
all: testclean $(AR_LIB)

# Linkage
$(AR_LIB): $(OBJ)
	$(AR) rcs $(AR_LIB) $(OBJ)

# File-wise compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o$@ $(CPPFLAGS) $(CFLAGS)

# Tests compilation
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS)


# Remove compiled files (objects)
clean:
	@rm -rf $(OBJ_DIR)

# Reset the project to its initial state
distclean: clean docclean testclean
	@rm -rf $(AR_LIB)

# (Re)generate documentation
doc:
	@$(DOC_PRG) $(DOC_CFG)

# Remove documentation
docclean:
	@rm -rf $(DOC_DIR)

# Build and launch tests
test: $(TEST_OBJ) $(AR_LIB)
	$(CC) -o$(TEST_EXEC) $^ $(LDLIBS) $(LDFLAGS)
	./$(TEST_EXEC)

# Remove test build files
testclean:
	@rm -rf $(TEST_OBJ) $(TEST_EXEC) $(TEST_LOG)

# Install the project for system use
install:
	@cp --update --target-directory=$(INST_DIR)/include $(INC_DIR)/*.h
	@cp --update --target-directory=$(INST_DIR)/lib $(AR_LIB)

# Remove the project from the system
uninstall:
	@rm -f $(patsubst $(INC_DIR)/%,$(INST_DIR)/include/%,$(wildcard $(INC_DIR)/*))
	@rm -f $(INST_DIR)/lib/$(AR_LIB)
