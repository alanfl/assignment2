FLAGS= -Wall -Werror -fsanitize=address -std=c99
CC=gcc
LIBS = -lm -lpthread

all:
	$(error please compile with target 'proc' or 'thread')

proc: searchtest.o multitest_proc.o
	$(CC) $(FLAGS) $(LIBS) -o $@ $^

thread: searchtest.o multitest_thread.o
	$(CC) $(FLAGS) $(LIBS) -o $@ $^ 

multitest_thread.o: multitest_thread.c multitest.h
	$(CC) $(FLAGS) -c $<

multitest_proc.o: multitest_proc.c multitest.h
	$(CC) $(FLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o *.i *.bc *.s thread proc
