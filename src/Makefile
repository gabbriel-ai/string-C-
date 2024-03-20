MAIN_FLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -I/usr/local/include

COV_FLAGS = -fprofile-arcs -ftest-coverage

FUNCS = s21_strlen.c s21_strpbrk.c s21_strerror.c s21_strcspn.c s21_strncmp.c s21_strncpy.c s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strchr.c s21_strncat.c s21_strrchr.c s21_strstr.c s21_strtok.c s21_insert.c s21_to_upper.c s21_to_lower.c s21_trim.c s21_sprintf.c

OBJS = $(FUNCS:.c=.o)

SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    SYSTEM_FLAGS =  -lcheck -lpthread -lrt -lsubunit -lm
else ifeq ($(SYSTEM), Darwin)
    SYSTEM_FLAGS = -lcheck
endif

all: clean s21_string.a test gcov_report style

s21_string.a: $(OBJS)
	ar rcs s21_string.a $(OBJS)

test:
	gcc $(MAIN_FLAGS) tests/test_s21_string.c s21_string.a -o test $(SYSTEM_FLAGS)
	./test

gcov_report:
	gcc $(MAIN_FLAGS) $(COV_FLAGS) $(FUNCS) tests/test_s21_string.c -o test $(SYSTEM_FLAGS)
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report

style:
	clang-format -n -style=Google *.c *.h

clean:
	rm -f *.gcno *.gcda *.o coverage.info test
	rm -rf coverage_report
	rm -f s21_string.a
