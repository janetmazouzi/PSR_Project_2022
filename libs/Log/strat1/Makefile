TARGET = liblog_dns1.so


all: $(TARGET)
$(TARGET) : log_dns1.o
	$(CC) -shared -Wl,-soname,liblog_dns1.so.1 -o liblog_dns1.so.1.0 $+
	ln -sf liblog_dns1.so.1.0 liblog_dns1.so
	ln -sf liblog_dns1.so.1.0 liblog_dns1.so.1
	-mv $(@)* ../../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^


debug: CFLAGS+=-g -DDEBUG

clean :
	rm -f *.o *.so* *~ .*.un*
	rm -f ../../../*.txt
