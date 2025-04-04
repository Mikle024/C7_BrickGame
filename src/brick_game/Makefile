LIBRARY		= s21_tetris.a
FUNC_FILES	= tetris/s21_*.c
INC 		= tetris/inc/*.h
OBJ			= object/s21_*.o
FUNC_TEST	= tests/test_s21_*.c
MAIN_TEST	= tests/tests_main.c
INC_TEST	= tests/s21_tests.h
OBJ_TEST	= object_test/test_s21_*.o
OUT_TEST	= tetris_test
REPORT_DIR  = report
REPORT_FILE	= $(REPORT_DIR)/index.html

FILE_SCORE = highScore.txt

UNAME_S := $(shell uname -s)

CC			= gcc
CFLAGS		= -c -std=c11
L_FLAGS		= -std=c11 -Wall -Werror -Wextra
COVER_FLAG  = --coverage
LIB_FLAGS 	= ar rcs

ifeq ($(UNAME_S), Linux)
	OS_SPECIFIC_FLAGS 				= -lcheck -lsubunit -lm
	OS_SPECIFIC_GCOV_REPORT 		= branch_coverage=1
	OS_SPECIFIC_GCOV_REPORT_HTML 	= branch_coverage=1
else ifeq ($(UNAME_S), Darwin)
	OS_SPECIFIC_FLAGS 				= -lcheck
    OS_SPECIFIC_GCOV_REPORT 		= branch_coverage=1
    OS_SPECIFIC_GCOV_REPORT_HTML 	= branch_coverage=1
endif

ifeq ($(shell grep -i microsoft /proc/version),)
	OPEN_REPORT:= open
else
    OPEN_REPORT:= wslview
endif

all: s21_tetris.a

s21_tetris.a: build.o
	$(LIB_FLAGS) $(LIBRARY) $(OBJ)

test: test_build
	./$(OUT_TEST) && rm $(FILE_SCORE)

test_with_report: test
	$(MAKE) gcov_report
	-rm -rf *.gcda *.gcno $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY) $(FILE_SCORE)
	$(OPEN_REPORT) $(REPORT_FILE)

leaks_test: test_build
	leaks -atExit -- ./$(OUT_TEST)
	-rm -rf *.gcda *.gcno *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY) $(FILE_SCORE)

valgrind_test: test_build
	valgrind --leak-check=full ./$(OUT_TEST)
	-rm -rf *.gcda *.gcno *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY) $(FILE_SCORE)

test_build: clean s21_tetris.a_for_test build_test.o
	$(CC) $(L_FLAGS) $(COVER_FLAG) $(OBJ_TEST) $(MAIN_TEST) -L. $(LIBRARY) $(OS_SPECIFIC_FLAGS) -o $(OUT_TEST)

s21_tetris.a_for_test: build_object_for_test.o
	$(LIB_FLAGS) $(LIBRARY) $(OBJ)
	rm -fr $(OBJ)

build.o:
	mkdir -p object && $(CC) $(CFLAGS) -c $(FUNC_FILES) && mv s21_*.o object/

build_object_for_test.o:
	mkdir -p object && $(CC) $(CFLAGS) $(COVER_FLAG) -c $(FUNC_FILES) && mv s21_*.o object/

build_test.o:
	mkdir -p object_test && \
	$(CC) $(CFLAGS) -c $(FUNC_TEST) && mv test_s21_*.o object_test/

gcov_report:
	mkdir -p $(REPORT_DIR)
	lcov -t "tetris" -o tetris.info -c -d . \
		--exclude "*/tests/*" \
		--rc $(OS_SPECIFIC_GCOV_REPORT) \
		--rc lcov_function_coverage=1 \
		--rc lcov_branch_coverage=1
	genhtml -o $(REPORT_DIR) tetris.info \
		--rc $(OS_SPECIFIC_GCOV_REPORT_HTML) \
		--function-coverage \
		--branch-coverage \
		--legend \
		--demangle-cpp

clang_format:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i $(FUNC_FILES) $(INC) $(FUNC_TEST) $(MAIN_TEST) $(INC_TEST) $(UTILS_TEST)
	rm -f .clang-format

rebuild: clean all

clean:
	rm -rf object/ object_test/ $(OUT_TEST) $(LIBRARY) *.gcda *.gcno *.o $(REPORT_DIR)/ *.info rm $(FILE_SCORE)