export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/../../dynamic
CC = gcc
CFLAGS=-Wall -Wextra -Werror
TARGET = testMemory
LFLAGS = -L ../../dynamic/ -lmemoire


all: $(TARGET)
$(TARGET) : testMemory.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -I ../ 


clean :
	rm -f *.o  $(TARGET)
