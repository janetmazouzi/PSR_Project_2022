SUBDIRS = strat1 strat2 stratchoice

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
	rm -rf ../dynamic/*.so*
	rm -rf *~ .*.un*
