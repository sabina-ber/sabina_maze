.PHONY: all build clean

FLAGS=-g++ -Wall -Wextra -Werror -pedantic -std=c++17
TEST_FLAGS=-lgtest -pthread
SOURCE = model/maze.cc model/mazegenerator.cc model/cell.cc
OS_DEPENDENT_FLAGS = -lgtest -lpthread -fprofile-arcs -ftest-coverage
TEST_FILES = tests/test.cc

all: install

install: uninstall
	mkdir -p build
	cd build && cmake ..
	make -C build

uninstall:
	rm -rf A1_Maze.tar
	rm -rf build
	rm -rf A1_Maze.app
	
run:
	cd build && open Maze.app

dvi:
	doxygen Doxyfile
	cd docs/html && open index.html
		
dist:
	tar -C ./build -cf A1_Maze.tar A1_Maze.app

test:
	cd build && ./Maze_test
	cd build && make coverage && cd out && open index.html
	
test_usual:
	$(FLAGS) $(SOURCE) tests/test.cc $(TEST_FLAGS) -o test
	./test

gcov_report:
	$(FLAGS) --coverage $(SOURCE) $(TEST_FILES) -o test -g $(OS_DEPENDENT_FLAGS)
	./test
	lcov -t "test" -c -d ./ --no-external -o test.info
	genhtml -o report test.info

clean:
	rm -rf *.gcno *.gcda
	rm -rf test_output
	rm -rf build
	rm -rf test test.info
	rm -Rf html/ latex/
	rm -rf A1_Maze.app
	rm -rf *.tar
	rm -rf docs
	rm -rf report
	rm -rf test.dSYM

