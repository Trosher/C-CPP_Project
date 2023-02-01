WWW = -Wall -Werror -Wextra
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: clean install

install:
	@cd 3d_viever/ && qmake && make && make clean && rm -rf Makefile

tests: clean
	@gcc $(WWW) -std=c11 -fprofile-arcs -ftest-coverage tests.c 3d_viever/C_file/pars_obj/pars_obj.c 3d_viever/C_file/Afina/afina.c 3d_viever/C_file/struct.c -o unit_test -lcheck
	@./unit_test

check:
	@cp ../materials/linters/.clang-format .
	@echo *.c files
	@clang-format -n 3d_viever/C_file/*.c
	@echo *.cpp files
	@clang-format -n 3d_viever/*.cpp
	@echo *.h files
	@clang-format -n 3d_viever/*.h
	@clang-format -n 3d_viever/C_file/*.h
	@rm -rf .clang-format

uninstall:
	@cd 3d_viever/ && rm -rf *.app

dist:
	tar -cf dist_tar.zip 3d_viever/aga_v2.app

dvi:
	open dvi.html

gcov_report: clean_test clean_lib
	@gcc -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage tests.c 3d_viever/C_file/pars_obj/pars_obj.c 3d_viever/C_file/Afina/afina.c 3d_viever/C_file/struct.c -o unit_test -lcheck
	@./unit_test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	@open report/index.html

valgf: tests
	@valgrind --leak-check=full --track-origins=yes -s ./unit_test

clean_obj:
	@rm -rf *.o

clean_lib: 
	@rm -rf *.a

clean_test:
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf report

clean: clean_lib clean_lib clean_test clean_obj
	@rm -rf unit_test
	@rm -rf a.out
