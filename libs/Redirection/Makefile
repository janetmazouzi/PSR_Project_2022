
TARGET = libredirection.so


all: $(TARGET)
$(TARGET) : redirection.o
	$(CC) -shared -Wl,-soname,libredirection.so.1 -o libredirection.so.1.0 $+
	ln -sf libredirection.so.1.0 libredirection.so
	ln -sf libredirection.so.1.0 libredirection.so.1
	-mv $(@)* ../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^ 



clean :
	rm -f *.o *.so* 
	rm -rf *~ .*.un* .*.swp
