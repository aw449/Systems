CC=gcc
CCFLAGS= -Wall -g

Main:  Main.o Node.o sorted-list.o
	$(CC)  Main.o Node.o sorted-list.o -o pa2

Main.o: Main.c
	$(CC) $(CCFLAGS) -c Main.c

Node.o: Node.c
	$(CC) $(CCFLAGS) -c Node.c

sorted-list.o: sorted-list.c
	$(CC) $(CCFLAGS) -c sorted-list.c

clean:
	rm -f *.o
	rm pa2
