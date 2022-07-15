CC = g++
CFLAGS = -Wall -O3 -std=c++20
SOURCE = Converter.cpp Main.cpp
INCLUDES = -I../Includes

all: Converter

Converter: $(SOURCE)
	$(CC) $(CFLAGS) $(INCLUDES) -o ../Converter $(SOURCE)

clean:
	rm -f *.o Converter
