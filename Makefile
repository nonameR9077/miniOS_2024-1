# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude `pkg-config --cflags gtk+-3.0`
# Linker flags
LDFLAGS=-lreadline -lpthread `pkg-config --libs gtk+-3.0`

# The build target executable:
TARGET=minios

# Source, Object files
SRCS=kernel/kernel.c kernel/system.c kernel/20180624/fork.c kernel/20180624/ipc.c kernel/20180624/rr.c
OBJS=$(SRCS:.c=.o) 

# Include directory
INCLUDE_DIR=include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up:
clean:
	rm -f $(OBJS) $(TARGET)
