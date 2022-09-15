
export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/../../dynamic
CC = gcc
CFLAGS=-Wall -Wextra -Werror
TARGET = testReseau
LFLAGS = -L ../../static -lreseau


all: $(TARGET)
$(TARGET) : testReseau.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -I ../ 
debug : all
debug: CFLAGS+=-g -DDEBUG

clean :
	rm -f *.o  $(TARGET) .*.un* *~
