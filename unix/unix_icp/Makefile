CFLAGS=-c -Wall
LDFLAGS=-lrt
EXECUTABLE1=icp_1
EXECUTABLE2=icp_2
SOURCE1=icp_1.c
SOURCE2=icp_2.c

all: $(SOURCE1) $(EXECUTABLE1) $(SOURCE2) $(EXECUTABLE2)

$(EXECUTABLE1): main1.o
	gcc main1.o -o $(EXECUTABLE1) $(LDFLAGS)

main1.o: $(SOURCE1)
	gcc $(CFLAGS) $(SOURCE1) -o main1.o

$(EXECUTABLE2): main2.o
	gcc main2.o -o $(EXECUTABLE2) $(LDFLAGS)

main2.o: $(SOURCE2)
	gcc $(CFLAGS) $(SOURCE2) -o main2.o

clean:
	rm -rf *.o $(EXECUTABLE1) $(EXECUTABLE2)
