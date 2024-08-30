TARGET = main
CC = gcc
CFLAGS = -Wall

all: debug

debug: CFLAGS += -g
debug: $(TARGET)

release: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

clean:
	rm -f $(TARGET)