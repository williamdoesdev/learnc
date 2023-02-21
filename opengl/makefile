all: opengl

CC = gcc
CFLAGS = 
LIBS = -lglfw -lGL -lGLEW

opengl: main.o fileio.o glerror.o vertexbuffer.o indexbuffer.o
	$(CC) $(CFLAGS) -o opengl main.o fileio.o glerror.o vertexbuffer.o indexbuffer.o $(LIBS)
	
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

fileio.o: src/fileio.c
	$(CC) $(CFLAGS) -c src/fileio.c

glerror.o: src/glerror.c
	$(CC) $(CFLAGS) -c src/glerror.c

vertexbuffer.o: src/vertexbuffer.c
	$(CC) $(CFLAGS) -c src/vertexbuffer.c

indexbuffer.o: src/indexbuffer.c
	$(CC) $(CFLAGS) -c src/indexbuffer.c

clean:
	rm -f *.o opengl