# I had ChatGPT help me with this as my original would not work correctly
# I had the header file in here and that was causing the problem

CC = gcc
CFLAGS = -Wall -g

# Target executable
TARGET = list_test

# Source files
SRCS = list.c list_test.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for compiling .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
