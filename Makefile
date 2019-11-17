#
# FILE:         Makefile
# DESCRIPTION:  Some linux process related tests
#


CXXFLAGS :=
CC := clang -Wall -ansi
PRGS := forkdemo tinyshell zombiefarm sysenv errno openlimit lseeking fdtest \
		dupe pids
TEST := testfile

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

openlimit: openlimit.c
	clang -Wall -std=c99 -o $@ $<

lseeking: lseeking.c
	clang -Wall -std=c99 -o $@ $<

fdtest: fdtest.c
	clang -Wall -std=c99 -o $@ $<

dupe: dupe.c
	clang -Wall -std=c99 -o $@ $<

pids: pids.c
	clang -Wall -std=c99 -o $@ $<

size:
	@echo "# text: Machine code"
	@echo "# data: Initilized global data"
	@echo "# bss:  Uninitialized global data"
	@echo "# dec/hex: Sum of previous fields"
	@size $(PRGS)

clean:
	@rm -f *~ src/*.o src/*~
	@rm -f output.txt $(TEST)

distclean: clean
	@rm -f $(PRGS)

