TARGET = libmemoire.so


all: $(TARGET)
$(TARGET) : memoire.o
	$(CC) -shared -Wl,-soname,libmemoire.so.1 -o libmemoire.so.1.0 $+
	ln -sf libmemoire.so.1.0 libmemoire.so
	ln -sf libmemoire.so.1.0 libmemoire.so.1
	-mv $(@)* ../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^


clean :
	rm -f *.o ../dynamic/*.so*
	rm -rf *~ .*.un*
