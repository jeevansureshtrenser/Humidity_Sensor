# Compiler and Flags
CC      = wr-cc
CFLAGS  = -rtp -static -Iinclude
TARGET  = humiditysensor.vxe
SRC     = main.c monitor.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)