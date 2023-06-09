# Variables
CC := gcc
CFLAGS := -Wall -Wextra
LIBRARY := hlib.so

# Source directories
SRC_DIRS := hmalloc data_structures

# Source files (.c files) in the source directories
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Object files
OBJECTS := $(SOURCES:.c=.o)

# Header files (.h files) in the source directories
HEADERS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))

# Default target
all: $(LIBRARY)

# Build the shared library
$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) -shared $^ -o $@

# Rule to compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Clean up object and library files
clean:
	rm -f $(OBJECTS) $(LIBRARY)

