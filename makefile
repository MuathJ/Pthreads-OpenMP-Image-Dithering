CC=g++
CFLAGS=-I -O3 -Wall

DEPS=
OBJ = serial_code.o .o p_thread.o
all:  serial_code p_thread

serial_code: serial_code.o
		$(CC) -o $@ $^
p_thread: p_thread.o
		g++ -Wall -pthread -o p_thread p_thread.cpp
		
%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)
		
serial: serial_code
		time ./serial_code oimage.txt mask.txt output-serial.txt
		
pthread: p_thread
		 time ./p_thread oimage.txt mask.txt output-pthread.txt 20
		
clean:
		rm -f *.o *~ core

