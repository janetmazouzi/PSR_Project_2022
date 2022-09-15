export CC=gcc
export CFLAGS=-Wall -Wextra -Werror
export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/libs/dynamic
SUBDIRS = libs src

all:
	for dir in $(SUBDIRS); do \
		($(MAKE) -C $$dir -f Makefile $@;) || exit $$?; \
	done


debug: all
#debug: MAKE1+= all
debug: CFLAGS+=-g -DDEBUG

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
	rm -rf *~ .*.un*

install_hook:
	cp ../hooks/pre-commit ../.git/hooks
