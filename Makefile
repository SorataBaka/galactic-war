FLAGS = -lncursesw

all: glwar

glwar: main.o draw.o util.o game.o endscreen.o mainscreen.o leaderboard.o settings.o
	gcc main.o draw.o util.o game.o endscreen.o mainscreen.o leaderboard.o settings.o -o glwar -lncurses -lm -g

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

mainscreen.o: src/mainscreen.c src/mainscreen.h
	cc -c src/mainscreen.c src/mainscreen.h

leaderboard.o: src/leaderboard.c src/leaderboard.h
	cc -c src/leaderboard.c src/leaderboard.h

settings.o: src/settings.c src/settings.h
	cc -c src/settings.c src/settings.h
	
clean:
	-rm *.o src/*.gch

distclean:	clean
	-rm glwar

dist: distclean
	(tar --exclude ./.git -zcvf glwar.tgz . )


.SUFFIXES: .c .o
.PHONY:  all clean distclean dist
