EXEC = ../bin/main
EXEC2=../bin/dnsproxy_mgr
LFLAGS =-L ../libs/dynamic -lgenericLog -L ../libs/dynamic -lthread -L ../libs/dynamic -lmemoire -L ../libs/dynamic -lredirection -L ../libs/static/ -lreseau  -ldl -lpthread

all: $(EXEC) $(EXEC2)

$(EXEC) : main.o args.o  
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
$(EXEC2) : dnsproxy_mgr.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)



%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I ../libs/Log/stratchoice -I ../libs/Threads/ -I ../libs/Memoire/ -I ../libs/Redirection/



clean : # cible de nettoyage 
	rm -f *.o *~
	rm -f $(EXEC) $(EXEC2)
	rm -rf *~ .*.un* *.swp*
