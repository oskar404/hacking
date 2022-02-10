#
# FILE:         Makefile
# DESCRIPTION:  Some linux process related tests
#


CXXFLAGS :=
CC := clang -Wall -ansi
PRGS := forkdemo tinyshell zombiefarm sysenv errno openlimit lseeking fdtest \
		dupe pids piddata pidenv jmp mem main0 main1 main2 execve
#PRGS := forkdemo tinyshell zombiefarm sysenv errno openlimit lseeking fdtest \
#		dupe pids piddata pidenv jmp mem usr
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

piddata: pids
	ln -s pids piddata

pidenv: pids
	ln -s pids pidenv

jmp: jmp.c
	clang -Wall -std=c99 -o $@ $<

mem: mem.c
	clang -Wall -std=c99 -o $@ $<

#usr: usr.c
#	clang -Wall -std=c99 -o $@ $<

main0: main.c
	clang -Wall -std=c99 -o $@ $<

main1: main.c
	clang -DSIG1 -Wall -std=c99 -o $@ $<

main2: main.c
	clang -DSIG2 -Wall -std=c99 -o $@ $<

execve: execve.c
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
