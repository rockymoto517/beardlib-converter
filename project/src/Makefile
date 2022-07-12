CC = g++
CFLAGS = -Wall -O3 -std=c++20
SOURCE = Converter.cpp Main.cpp

all: Converter

Converter: $(SOURCE)
	$(CC) $(CFLAGS) -o ../Converter $(SOURCE)

clean:
	rm -f *.o Converter
