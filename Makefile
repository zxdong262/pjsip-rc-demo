# If your application is in a file named main.cpp or main.c
# this is the line you will need to build the binary.
all: main

main: main.cpp
	$(CC) -std=c++11 -o $@ $< `pkg-config --cflags --libs libpjproject`

clean:
	rm -f main.o main