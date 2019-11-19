all: dirinfo.o
	gcc -o program dirinfo.o

dirinfo.o: dirinfo.c dirinfo.h
	gcc -c dirinfo.c dirinfo.h

run:
	./program

clean:
	rm *.o
	rm *~
