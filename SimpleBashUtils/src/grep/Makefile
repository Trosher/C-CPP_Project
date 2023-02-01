WWW = -Wall -Wextra -Werror -std=c11

all: clean s21_grep test

s21_grep: clean
	gcc $(WWW) s21_grep.h s21_grep.c list.c -o s21_grep

test:
	sh t_grep.sh

clean:
	rm -rf log.txt
	rm -rf s21_grep