FLAGS = -lncursesw

all: glwar

glwar: main.o
	gcc main.o -o glwar -lncursesw

main.o: main.c definition.h

.c.o:
	cc -c $< $(FLAGS)

clean:
	rm *.o

.SUFFIXES: .c .o

.PHONY:  all