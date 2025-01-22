SHELL:=/bin/bash
CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
FILE=f1_test.txt
FILE2=f2_test.txt
all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(FLAGS) -o s21_grep s21_grep.o

clean: clean_obj
	rm -rf s21_grep .clang-format

clean_obj:
	rm -rf *.o

clang-i:
	cp ../../materials/build/scripts/.clang-format .clang-format
	clang-format -i s21_grep.c s21_grep.h

clang-n:
	cp ../../materials/build/scripts/.clang-format .clang-format
	clang-format -n s21_grep.c s21_grep.h

tests:
	-diff -s <(./s21_grep -f $(FILE2) $(FILE)) <(grep -f $(FILE2) $(FILE))
	-diff -s <(./s21_grep -f $(FILE2) $(FILE2)) <(grep -f $(FILE2) $(FILE2))
	-diff <(./s21_grep -n more $(FILE2) $(FILE)) <(grep -n more $(FILE2) $(FILE))
	-diff <(./s21_grep -n from $(FILE)) <(grep -n from $(FILE))
	-diff <(./s21_grep -e ^My $(FILE2)) <(grep -e ^My $(FILE2))
	-diff <(./s21_grep -nivh = $(FILE2) $(FILE)) <(grep -nivh = $(FILE2) $(FILE))
	-diff <(./s21_grep -ie HE $(FILE)) <(grep -ie HE $(FILE))
	-diff <(./s21_grep -elove $(FILE)) <(grep -elove $(FILE))
	-diff <(./s21_grep -ne = -e he $(FILE)) <(grep -ne = -e he $(FILE))
	-diff <(./s21_grep -e from -e ^My $(FILE) -v) <(grep -e from -e ^My $(FILE) -v)
	-diff <(./s21_grep ./s21_grep -f $(FILE2) $(FILE)) <(grep ./s21_grep -f $(FILE2) $(FILE))

val:
	bash test_leaks.sh

cpp:
	cppcheck —enable=all —suppress=missingIncludeSystem s21_grep.c
