CC = gcc
AR = ar
TARGET = liblog_dns2.so

all: $(TARGET) 

$(TARGET) : log_dns2.o
	$(CC) -shared -Wl,-soname,liblog_dns2.so.1 -o liblog_dns2.so.1.0 $+
	ln -sf liblog_dns2.so.1.0 liblog_dns2.so
	ln -sf liblog_dns2.so.1.0 liblog_dns2.so.1
	-mv $(@)* ../../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -I ../../Reseau

debug: CFLAGS+=-g -DDEBUG

clean :
	rm -f *.o *.so*
	rm -rf *~ .*.un*
