CFLAGS=-lstdc++ -std=c++17 -Wall -Werror -Wextra 

all: uninstall clean s21_matrix_oop.a clean test valgrind 
rebuild: uninstall clean all

s21_matrix_oop.a: build_lib

build_lib: objects
	@ar rc s21_matrix_oop.a s21_matrix_oop.o s21_hellp_matrix.o
	@ranlib s21_matrix_oop.a

objects:
	@gcc $(CFLAGS) -c s21_matrix_oop.cpp s21_hellp_matrix.cpp 

test: clean s21_matrix_oop.a tests.cpp
	@gcc $(CFLAGS) -lgtest tests.cpp s21_matrix_oop.a -o test
	@./test 

test_leak: clean s21_matrix_oop.a tests.cpp
	@gcc $(CFLAGS) -lgtest tests.cpp s21_matrix_oop.a -o test
	@leaks -atExit -- ./test 

uninstall:
	@rm -rf *a

clean:
	@rm -rf ./test CPPLINT.cfg *.gcno *.gcda
	@rm -rf ./test
	@rm -rf CPPLINT.cfg
	@rm -rf *.o

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h *.cpp
	rm -rf .clang-format
