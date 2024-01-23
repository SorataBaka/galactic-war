FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o util.o
	gcc main.o draw.o util.o -o glwar -lncurses -lm -g
	rm *.o src/*.gch

main.o: src/main.c src/definition.h src/draw.h
	cc -c src/main.c src/definition.h src/draw.h

draw.o: src/draw.c src/draw.h
	cc -c src/draw.c src/draw.h

util.o: src/util.c src/util.h
	cc -c src/util.c src/util.h
	
clean:
	rm *.o src/*.gch glwar

.SUFFIXES: .c .o
.PHONY:  all clean 
