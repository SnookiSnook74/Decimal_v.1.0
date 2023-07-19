CC=gcc
OS=$(shell uname)
WILD=$(wildcard */*.c)
WILD_REPORT_NO_TEST=$(shell find . -name "*.c" ! -name "*test*");
FLAGS=-Wall -Werror -Wextra
ifeq ($(OS), Linux)
  FLAGS_LCHECK = -lcheck -pthread -lsubunit -lrt -lm
  OPEN=xdg-open
else
  FLAGS_LCHECK = -lcheck
  OPEN=open
endif
FLAGS_GCOV = -coverage -fprofile-arcs -ftest-coverage
FILE_TEST = ./test/test.c

all: clean test

.PHONY: test
test: s21_decimal.a
	$(CC) -c $(WILD)
	$(CC) -o unit_test *.o $(FLAGS) $(FLAGS_LCHECK)

.PHONY: gcov_report
gcov_report: s21_decimal.a
		$(CC) $(FLAGS) $(wildcard */*.c) \
		$(FLAGS_LCHECK) $(FLAGS_GCOV) \
		 -o info -lm
	./info
	lcov -t "info" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	$(OPEN) report/index.html

.PHONY: s21_decimal.a
s21_decimal.a:
	$(CC) -c $(WILD_REPORT_NO_TEST)
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

.PHONY: docker
docker:
	docker rmi -f string && docker build -t string . && docker run --name unit string
	# docker cp unit:/hello/report .
	docker rm unit

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

style:
	clang-format -i */*.c
	clang-format -i */*.h

clean_no_all:
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info

clean:
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info
	rm -f *.a
	rm -rf report
	rm -f unit_test

.PHONY: git
git: style
	rm -rf report
	git add .
	git commit -m "commit"
	git push
