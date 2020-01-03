#
# FILE:         Makefile
# DESCRIPTION:  Some valgrind testing
#

CC := gcc -g -Wall -std=c99 -pedantic
CXX := g++ -g -std=c++11
VG := valgrind --leak-check=yes --tool=memcheck --show-reachable=yes
PRGS := crasher undef

all: $(PRGS)

crasher: crasher.c
	$(CC) $^ -o $@

undef: undef.cpp
	$(CXX) $^ -o $@

clean:
	@rm -f *~ *.o

distclean: clean
	@rm -f $(PRGS)

test-crasher: crasher
	$(VG) ./$<

test-undef: undef
	$(VG) ./$<
