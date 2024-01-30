FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o util.o game.o endscreen.o mainscreen.o leaderboard.o settings.o
	gcc main.o draw.o util.o game.o endscreen.o mainscreen.o leaderboard.o settings.o -o glwar -lncurses -lm -g

main.o: src/main.c src/definition.h src/definition.h src/mainscreen.h
	cc -c src/main.c src/definition.h src/definition.h src/mainscreen.h

draw.o: src/draw.c src/draw.h src/definition.h
	cc -c src/draw.c src/draw.h src/definition.h

game.o: src/game.c src/game.h src/definition.h
	cc -c src/game.c src/game.h src/definition.h

util.o: src/util.c src/util.h 
	cc -c src/util.c src/util.h

endscreen.o: src/endscreen.c src/endscreen.h src/definition.h src/draw.h src/util.h
	cc -c src/endscreen.c src/endscreen.h src/definition.h src/draw.h src/util.h

mainscreen.o: src/mainscreen.c src/mainscreen.h src/game.h src/endscreen.h src/definition.h src/leaderboard.h src/settings.h src/draw.h
	cc -c src/mainscreen.c src/mainscreen.h src/game.h src/endscreen.h src/definition.h src/leaderboard.h src/settings.h src/draw.h

leaderboard.o: src/leaderboard.c src/leaderboard.h src/definition.h
	cc -c src/leaderboard.c src/leaderboard.h src/definition.h

settings.o: src/settings.c src/settings.h src/definition.h src/draw.h
	cc -c src/settings.c src/settings.h src/definition.h src/draw.h
	
clean:
	-rm *.o src/*.gch

distclean:	clean
	-rm glwar

dist: distclean
	(tar --exclude ./.git -zcvf glwar.tgz . )


.SUFFIXES: .c .o
.PHONY:  all clean distclean dist
