OUT_GAME	= s21_BrickGame
BACKEND		= s21_tetris.a
MAIN		= s21_main.c
FRONT 		= gui/cli/s21_frontend.c

CC			= gcc
CFLAGS		= -c -std=c11
L_FLAGS		= -std=c11 -Wall -Werror -Wextra

all: install

install: s21_tetris.a
	mkdir -p ../build
	$(CC) $(L_FLAGS) $(MAIN)  $(FRONT) -lncurses -L. brick_game/$(BACKEND) -o $(OUT_GAME)
	mv $(OUT_GAME) ../build/

s21_tetris.a:
	$(MAKE) -C brick_game $(BACKEND)

test:
	$(MAKE) -C brick_game test

clang_format:
	$(MAKE) -C brick_game clang_format
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c $(FRONT) gui/cli/inc/*.h
	rm .clang-format

rebuild: clean all

clean:
	$(MAKE) -C brick_game clean
	rm -rf ../build