export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/../../dynamic
CC = gcc
CFLAGS=-Wall -Wextra -Werror -g
TARGET = testLog
LFLAGS = -L ../../dynamic/ -lgenericLog -ldl


all: $(TARGET)
$(TARGET) : testLog.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -I ../stratchoice/

debug: CFLAGS+=-g -DDEBUG

clean :
	rm -f *.o .*.un* *~ $(TARGET)
