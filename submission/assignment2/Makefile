FLAGS= -Wall -Werror -fsanitize=address -std=c99
CC=gcc
LIBS = -lm -lpthread

all:
	$(error please compile with target 'searchtest_proc' or 'searchtest_thread')

searchtest_proc: searchtest.o multitest_proc.o
	$(CC) $(FLAGS) $(LIBS) -o $@ $^

searchtest_thread: searchtest.o multitest_thread.o
	$(CC) $(FLAGS) $(LIBS) -o $@ $^ 

multitest_thread.o: multitest_thread.c multitest.h
	$(CC) $(FLAGS) -c $<

multitest_proc.o: multitest_proc.c multitest.h
	$(CC) $(FLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o *.i *.bc *.s searchtest_thread searchtest_proc
