TARGET=lab7-1

all: $(TARGET)

$(TARGET).tab.c $(TARGET).tab.h: $(TARGET).y
	bison -d $(TARGET).y

$(TARGET): $(TARGET).tab.c $(TARGET).tab.h
	gcc -o $(TARGET) $(TARGET).tab.c $(TARGET).tab.h

clean:
	rm -f $(TARGET) $(TARGET).tab.c $(TARGET).tab.h *~ core

new:
	make clean; make all
