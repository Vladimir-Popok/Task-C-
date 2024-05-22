CC = g++
CFLAGS = -Wall

all: task

task: Time.o Data.o BHours.o Managment.o Queue.o Scaner.o Visitors.o
	$(CC) $(CFLAGS) -o task Time.o Data.o BHours.o Managment.o Queue.o Scaner.o Visitors.o

Time.o: Time.cpp
	$(CC) $(CFLAGS) -c Time.cpp

Data.o: Data.cpp
	$(CC) $(CFLAGS) -c Data.cpp

BHours.o: BHours.cpp
	$(CC) $(CFLAGS) -c BHours.cpp

Managment.o: Managment.cpp
	$(CC) $(CFLAGS) -c Managment.cpp

Queue.o: Queue.cpp
	$(CC) $(CFLAGS) -c Queue.cpp

Scaner.o: Scaner.cpp
	$(CC) $(CFLAGS) -c Scaner.cpp

Visitors.o: Visitors.cpp
	$(CC) $(CFLAGS) -c Visitors.cpp

clean:
	rm -rf *.o task
