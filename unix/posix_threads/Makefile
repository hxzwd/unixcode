CFLAGS=-c -Wall
LDFLAGS=-lpthread
EXECUTABLE=posix_threads
SOURCES=main.c

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): main.o
	gcc main.o -o $(EXECUTABLE) $(LDFLAGS)

main.o: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES)

clean:
	rm -rf *.o $(EXECUTABLE)
