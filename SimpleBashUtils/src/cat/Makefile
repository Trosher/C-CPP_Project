WWW = -Wall -Wextra -Werror -std=c11

all: clean s21_cat test

s21_cat: clean
	gcc $(WWW) s21_cat.c -o s21_cat

test:
	sh t_cat.sh

clean:
	rm -rf log.txt
	rm -rf s21_cat
	rm -rf *o
	rm -rf *a
