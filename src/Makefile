TEST_L = -lcheck -lm -lpthread
OS := $(shell uname -s)
FILES = testProject/calc.c testProject/support.c testProject/validator.c testProject/test_function.c testProject/test_generated.c testProject/credit_calc.c
QMAKE = /Users/mac/QtFree/6.5.2/macos/bin/qmake
BUILD = ../build/
PRO_FILES = testProject/testProject.pro testProject/qcustomplot.h
TEST_FILES = testProject/test_function.c testProject/test_generated.c
FLAGS = -Wall -Wextra -Werror

ifneq ($(OS), Darwin)
	TEST_L += -lsubunit
endif

all: calc.a test gcov_report style

calc.a:
	gcc -c $(FILES) testProject/calc.h
	ar rcs calc.a *.o 
	ranlib calc.a 

install: 
	mkdir $(BUILD)
	cp $(PRO_FILES) $(BUILD)
	cd $(BUILD) && $(QMAKE) testProject.pro && make 
	open $(BUILD)testProject.app/Contents/MacOS/testProject

uninstall: 
	rm -rf $(BUILD)

dvi:
	makeinfo dvi.texi --html
	open ./dvi_html/index.html

dist: 
	cd .. && tar -czf SmartCalc-1.0.tgz src

test: calc.a
	checkmk calc_test.check > testProject/test_generated.c
	gcc $(FLAGS) $(TEST_FILES) -lcheck -L. calc.a -o test $(TEST_L) 
	./test

gcov_report: 
	checkmk calc_test.check > testProject/test_generated.c
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(FILES) -o test $(TEST_L) 
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

rebuild: clean all

clean:
	rm -rf test
	rm -rf *.a 
	rm -rf *.o 
	rm -rf test 
	rm -rf *.info 
	rm -rf *.gcda 
	rm -rf *.gcno 
	rm -rf *.gcov 
	rm -rf report 
	rm -rf .clang-format
	rm -rf dvi_html
	cd testProject && \
	rm -rf calc.h.gch 

style:
	cp ../materials/linters/.clang-format .
	clang-format -i testProject/*.c
	clang-format -i testProject/*.h
	clang-format -n testProject/*.c
	clang-format -n testProject/*.h

leaks:
	CK_FORK=no leaks --atExit -- ./test