LIBRARY		= s21_tetris.a
BACK_FUNC_FILES	= brick_game/s21_*.c
FRONT_FUNC_FILES = gui/s21_*.c
INC 		= inc/*.h
OBJ			= s21_*.o
FUNC_TEST	= tests/*/test_s21_*.c
MAIN_TEST	= tests/tests_main.c
TEST_HEADER	= tests/s21_tests.h
OBJ_TEST	= test_s21_*.o
OUT_TEST	= tetris_test
REPORT_FILE	= report/index.html

UNAME_S := $(shell uname -s)

CC			= gcc
CFLAGS		= -c -std=c11
L_FLAGS		= -std=c11 -Wall -Werror -Wextra
COVER_FLAG  = --coverage
LIB_FLAGS 	= ar rcs

ifeq ($(UNAME_S), Linux)
	OS_SPECIFIC_FLAGS 				= -lcheck -lsubunit -lm
	OS_SPECIFIC_GCOV_REPORT 		= branch_coverage=1
	OS_SPECIFIC_GCOV_REPORT_HTML 	= genhtml_branch_coverage=1
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

all: up

up:
	gcc brick_game/s21_backend.c brick_game/s21_brick_game.c  gui/s21_frontend.c brick_game/s21_fsm.c -lncurses -o tetris.out

build:
	$(CC) brick_game/main.c $(BACK_FUNC_FILES) $(FRONT_FUNC_FILES) -lncurses

s21_tetris.a: build.o
	$(LIB_FLAGS) $(LIBRARY) $(OBJ)
	rm -fr $(OBJ)

test: test_file
	./$(OUT_TEST)
	$(MAKE) gcov_report
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY)
	#$(OPEN_REPORT) $(REPORT_FILE)

leaks_test: test_file
	leaks -atExit -- ./$(OUT_TEST)
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY)

valgrind_test: test_file
	valgrind --leak-check=yes ./$(OUT_TEST)
	-rm -rf *.gc* *.info $(OUT_TEST) $(OBJ_TEST) $(OBJ) $(LIBRARY)

test_file: s21_tetris.a_for_test build_test.o
	$(CC) $(L_FLAGS) $(COVER_FLAG) $(OBJ_TEST) $(MAIN_TEST) -L. $(LIBRARY) $(OS_SPECIFIC_FLAGS) -o $(OUT_TEST)

s21_tetris.a_for_test: build_object_for_test.o
	$(LIB_FLAGS) $(LIBRARY) $(OBJ)
	rm -fr $(OBJ)

build.o:
	$(CC) $(CFLAGS) $(BACK_FUNC_FILES) $(FRONT_FUNC_FILES)

build_object_for_test.o:
	$(CC) $(CFLAGS) $(COVER_FLAG) $(BACK_FUNC_FILES) $(FRONT_FUNC_FILES)

build_test.o:
	$(CC) $(CFLAGS) $(BACK_FUNC_FILES)

gcov_report:
	lcov -t "test" -o tetris.info -c -d . --rc $(OS_SPECIFIC_GCOV_REPORT)
	genhtml -o report tetris.info --rc $(OS_SPECIFIC_GCOV_REPORT_HTML)

clang_format:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(BACK_FUNC_FILES) $(FRONT_FUNC_FILES) $(INC) $(FUNC_TEST) $(MAIN_TEST) $(TEST_HEADER)
	rm .clang-format

rebuild: clean all

clean:
	rm -rf $(OBJ) $(OUT_TEST) $(OBJ_TEST) $(LIBRARY) *.gc* report/ *.info