.PHONY: all test gcov_report check leaks valgrind rebuild clean clean_test

CC = g++ -m64 -Wall -Wextra -Werror -std=c++17
LIBS = -I/usr/local/include/ -L/usr/local/lib -lgtest -lpthread
TESTS = tests/*.cpp main.cpp

all: clean test gcov_report

test:
	$(CC) $(TESTS) -o test.out $(LIBS) 
	./test.out

gcov_report: clean_test
	$(CC) --coverage $(TESTS) -lstdc++ -o test.out $(LIBS)
	./test.out
	lcov -t "./test.out" --exclude='*.cpp' --ignore-errors source -o report.info --no-external -c -d .
	genhtml --ignore-errors source -o report report.info
	open ./report/index.html

check:
	clang-format -i *.ipp
	clang-format -i *.cpp
	clang-format -i *.h

leaks:
	$(CC) $(TESTS) -o main.out $(LIBS)
	leaks --atExit -- ./main.out
	rm -rf main.out

valgrind:
	$(CC) $(TESTS) -o main.out $(LIBS)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./main.out
	rm -f main.out

rebuild: clean all

clean: clean_test
	rm -rf ./report

clean_test:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov *.gch
