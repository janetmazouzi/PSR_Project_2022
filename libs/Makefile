SUBDIRS = Log Reseau Threads Memoire Redirection

all:
	for dir in $(SUBDIRS); do \
		($(MAKE) -C $$dir -f Makefile $@;) || exit $$?; \
	done

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
	rm -rf *~ .*.un*
