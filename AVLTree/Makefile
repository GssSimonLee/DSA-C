TARGET = main
CC = gcc
CFLAGS = -Wall
SOURCE = main.c

all: debug

debug: CFLAGS += -g
debug: $(TARGET)

release: $(TARGET)


$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)


clean:
	rm -f $(TARGET) *.o
