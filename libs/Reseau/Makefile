AR = ar
TARGET = ../static/libreseau.a 

all: $(TARGET)

$(TARGET) : reseau.o
	$(AR) -crs $@  $^


%.o : %.c
	$(CC) $(CFLAGS) -c $^



clean :
	rm -f *.o *.a $(EXEC)
	rm -f $(TARGET)
	rm -rf *~ .*.un*
