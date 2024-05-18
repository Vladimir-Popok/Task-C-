CC = g++
CFLAGS = -Wall

all: task

task: Time.o Data.o BHours.o Management.o Queue.o Scanner.o Visitors.o
	$(CC) $(CFLAGS) -o task Time.o Data.o BHours.o Management.o Queue.o Scanner.o Visitors.o

Time.o: Time.cpp
	$(CC) $(CFLAGS) -c Time.cpp

Data.o: Data.cpp
	$(CC) $(CFLAGS) -c Data.cpp

BHours.o: BHours.cpp
	$(CC) $(CFLAGS) -c BHours.cpp

Management.o: Management.cpp
	$(CC) $(CFLAGS) -c Management.cpp

Queue.o: Queue.cpp
	$(CC) $(CFLAGS) -c Queue.cpp

Scanner.o: Scanner.cpp
	$(CC) $(CFLAGS) -c Scanner.cpp

Visitors.o: Visitors.cpp
	$(CC) $(CFLAGS) -c Visitors.cpp

clean:
	rm -rf *.o task
