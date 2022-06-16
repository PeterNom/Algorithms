CFLAGS = -O
CC = g++

Test: main.o
 $(CC) $(CFLAGS) -o Test main.o
 
main.o: main.cpp
 $(CC) $(CFLAGS) -c main.cpp

 clean:
 rm -f core *.o
