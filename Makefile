FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o
	gcc main.o draw.o -o glwar -lncurses

main.o: src/main.c src/definition.h src/draw.h
	cc -c src/main.c src/definition.h src/draw.h

draw.o: src/draw.c src/draw.h
	cc -c src/draw.c src/draw.h

clean:
	rm *.o glwar

.SUFFIXES: .c .o
.PHONY:  all clean 
