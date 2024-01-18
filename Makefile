FLAGS = -lncursesw

all: glwar

glwar: src/main.o
	gcc main.o -o glwar -lncursesw

main.o: src/main.c src/definition.h

.c.o:
	cc -c $< $(FLAGS)

clean:
	rm *.o

.SUFFIXES: .c .o

.PHONY:  all