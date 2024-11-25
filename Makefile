GCC := g++ -Werror -Wextra -Wall --std=c++20 -lstdc++ -lm
SANITIZER :=  -fsanitize=address -fsanitize=leak -fsanitize=undefined
SOURSE :=  tests.cpp
FLAGS_LCOV := -g -fprofile-arcs -ftest-coverage
FLAGS_GTEST := -lgtest -lgcov -pthread

all: clean gcov_report

tests: clean
	$(GCC) $(SOURSE) $(FLAGS_LCOV) $(FLAGS_GTEST) -o s21_test_file
	./s21_test_file

gcov_report: tests #--ignore-errors mismatch 
	@lcov -t s21_test_file -o rep.info -c -d . --exclude '*/usr/*' --exclude '*/12/*'
	@genhtml -o report rep.info
	@rm -rf gcovreport gcovreport.info *.gcda *.gcno math_test.gcda math_test.gcno
	@open ./report/index.html

rebuild: clean all

clean: 
	rm -rf *.o s21_test_file s21_report *.a *.out *.gcno *.gcda s21_test.dSYM *.info report

check:
	clang-format --style=Google -n $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
	clang-format --style=Google -i $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
