#
# FILE:         Makefile
# DESCRIPTION:  Some valgrind testing
#

CC := gcc -g -Wall -std=c99 -pedantic
VG := valgrind --leak-check=yes --tool=memcheck --show-reachable=yes

all: crasher

%.o: %.cpp
	$(CXX) -c $< -o $@

crasher: crasher.c
	$(CC) $^ -o $@

clean:
	@rm -f *~ *.o

distclean: clean
	@rm -f crasher

valgrind: crasher
	$(VG) ./$<
