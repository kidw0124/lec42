TARGET=lab6-1

all: $(TARGET)

lex.yy.c: $(TARGET).l
	flex $(TARGET).l

$(TARGET): lex.yy.c 
	gcc -o $(TARGET) lex.yy.c -ll

clean:
	rm -f $(TARGET) lex.yy.c *~ core

new:
	make clean; make all
