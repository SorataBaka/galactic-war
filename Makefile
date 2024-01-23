FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o util.o game.o endscreen.o
	gcc main.o draw.o util.o game.o endscreen.o -o glwar -lncurses -lm -g
	rm *.o src/*.gch

main.o: src/main.c src/definition.h src/draw.h
	cc -c src/main.c src/definition.h src/draw.h

draw.o: src/draw.c src/draw.h
	cc -c src/draw.c src/draw.h

game.o: src/game.c src/game.h
	cc -c src/game.c src/game.h

util.o: src/util.c src/util.h
	cc -c src/util.c src/util.h

endscreen.o: src/endscreen.c src/endscreen.h
	cc -c src/endscreen.c src/endscreen.h
	
clean:
	rm *.o src/*.gch glwar

.SUFFIXES: .c .o
.PHONY:  all clean 
