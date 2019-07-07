#
# FILE:         Makefile
# DESCRIPTION:  Stub for development
#



#CXXFLAGS := `pkg-config --cflags libxml-2.0`
CXXFLAGS := 
CC := clang -Wall
    
all: forkdemo tinyshell zombiefarm

forkdemo: forkdemo.c
	$(CC) -o $@ $<

tinyshell: tinyshell.c
	$(CC) -o $@ $<

zombiefarm: zombiefarm.c
	$(CC) -o $@ $<

clean:
	@rm -f *~ src/*.o src/*~
	@rm -f output.txt

distclean: clean
	@rm -f forkdemo tinyshell zombiefarm

valgrind: forkdemo
	valgrind --leak-check=yes --tool=memcheck --show-reachable=yes ./$<

wc:
	@echo "Counting lines..."  
	@find src -name "*.[ch]*" -exec cat {} \; | wc -l

