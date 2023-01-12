TARGET := main.o

SOURCES := $(wildcard ./src/*.c)
HEADERS := ./include

CC := gcc
CCFLAGS := -std=c99

$TARGET: $(HEADERS) $(SOURCES)
	$(CC) $(CCFLAGS) -I$(HEADERS) $(SOURCES) -o $(TARGET)
asm: $(HEADERS) $(SOURCES)
	$(CC) $(CCFLAGS) -I$(HEADERS) $(SOURCES) -S src/main.c
