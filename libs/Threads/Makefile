TARGET = libthread.so


all: $(TARGET)
$(TARGET) : thread.o
	$(CC) -shared -Wl,-soname,libthread.so.1 -o libthread.so.1.0 $+
	ln -sf libthread.so.1.0 libthread.so
	ln -sf libthread.so.1.0 libthread.so.1
	-mv $(@)* ../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^



clean :
	rm -f *.o *.so* 
	rm -rf *~ .*.un*
