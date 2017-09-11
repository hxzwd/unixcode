CFLAGS=-c -Wall
LDFLAGS=-lpthread
EXECUTABLE=posix_mutex
SOURCES=main.c

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): main.o
	gcc main.o -o $(EXECUTABLE) $(LDFLAGS)

main.o: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES)

clean:
	rm -rf *.o $(EXECUTABLE)
