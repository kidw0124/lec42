TARGET=lab

all: $(TARGET)

lab.tab.c lab.tab.h:	lab.y
	bison -d lab.y

lex.yy.c: lab.l lab.tab.h
	flex lab.l

$(TARGET): lex.yy.c lab.tab.c lab.tab.h
	gcc -o $(TARGET) lab.tab.c lex.yy.c

clean:
	rm -f $(TARGET) lab.tab.c lex.yy.c lab.tab.h *~ core

new:
	make clean; make all
