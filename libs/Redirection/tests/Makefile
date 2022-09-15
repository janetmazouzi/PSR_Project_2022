export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/../../dynamic
CC = gcc
CFLAGS=-Wall -Wextra -Werror
TARGET = testredirection
LFLAGS = -L ../../dynamic/ -lredirection


all: $(TARGET)
$(TARGET) : testredirection.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -I ../ 


clean :
	rm -f *.o  $(TARGET)
