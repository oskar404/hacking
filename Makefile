#
# FILE:         Makefile
# DESCRIPTION:  Some linux process related tests
#


CXXFLAGS :=
CC := clang -Wall -ansi
PRGS := forkdemo tinyshell zombiefarm sysenv errno

all: $(PRGS)

forkdemo: forkdemo.c
	$(CC) -o $@ $<

tinyshell: tinyshell.c
	$(CC) -o $@ $<

zombiefarm: zombiefarm.c
	$(CC) -o $@ $<

sysenv: sysenv.c
	clang -Wall -Wno-#pragma-messages -std=c99 -o $@ $<

errno: errno.c
	clang -Wall -std=c99 -o $@ $<

clean:
	@rm -f *~ src/*.o src/*~
	@rm -f output.txt

distclean: clean
	@rm -f $(PRGS)

