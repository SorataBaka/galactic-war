FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o util.o
	gcc main.o draw.o util.o -o glwar -lncurses

main.o: src/main.c src/definition.h src/draw.h
	cc -c src/main.c src/definition.h src/draw.h

draw.o: src/draw.c src/draw.h
	cc -c src/draw.c src/draw.h

util.o: src/util.c src/util.h src/definition.h
	cc -c src/util.c src/util.h src/definition.h

clean:
	rm *.o glwar

.SUFFIXES: .c .o
.PHONY:  all clean 
