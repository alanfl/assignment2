FLAGS= -Wall -Werror -fsanitize=address -std=c99
CC=gcc

all:
	$(error please compile with target 'searchtest_proc' or 'searchtest_thread')

searchtest_proc: searchtest.o multitest_proc.o
	$(CC) $(FLAGS) -o $@ $^

searchtest_thread: searchtest.o multitest_thread.o
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c multitest.h
	$(CC) $(FLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o *.i *.bc *.s searchtest_thread searchtest_proc
