AR = ar
TARGET = libgenericLog.so

all: $(TARGET)

$(TARGET): genericLog.o
	$(CC) -fPIC -shared -Wl,-soname,libgenericLog.so.1 -o libgenericLog.so.1.0 $+
	ln -sf libgenericLog.so.1.0 libgenericLog.so
	ln -sf libgenericLog.so.1.0 libgenericLog.so.1
	-mv $(@)* ../../dynamic

%.o : %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -ldl 

debug: CFLAGS+=-g -DDEBUG
clean :
	rm -f *.o *.so*
	rm -rf *~ .*.un*
