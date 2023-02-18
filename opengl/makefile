all: opengl

CC = gcc
CFLAGS = 
LIBS = -lglfw -lGL -lGLEW

opengl: main.o fileio.o
	$(CC) $(CFLAGS) -o opengl main.o fileio.o $(LIBS)
	
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

fileio.o: src/fileio.c
	$(CC) $(CFLAGS) -c src/fileio.c

clean:
	rm -f *.o opengl