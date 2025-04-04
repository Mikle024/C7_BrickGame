OUT_GAME	= s21_BrickGame
BACKEND		= s21_tetris.a
MAIN		= s21_main.c
FRONT 		= gui/cli/s21_frontend.c

CC			= gcc
CFLAGS		= -c -std=c11
L_FLAGS		= -std=c11 -Wall -Werror -Wextra

all: install

install:
	$(MAKE) -C brick_game $(BACKEND)
	mkdir -p ../build
	$(CC) $(L_FLAGS) $(MAIN)  $(FRONT) -lncurses -L. brick_game/$(BACKEND) -o $(OUT_GAME)
	mv $(OUT_GAME) ../build/
	rm brick_game/s21_tetris.a && rm -r brick_game/object

uninstall:
	rm -rf ../build/$(OUT_GAME)

test:
	$(MAKE) -C brick_game test

dvi:
	@bash scripts/generate_dvi.sh

dist: clean install
	mkdir -p ../build
	tar -cf ../build/BrickGame.tar ./*
	gzip ../build/BrickGame.tar
	mv ../build/BrickGame.tar.gz ../build/BrickGame.tgz
	rm ../build/s21_BrickGame

gcov_report:
	$(MAKE) -C brick_game gcov_report

rebuild: clean all

clang_format:
	$(MAKE) -C brick_game clang_format
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h $(FRONT) gui/cli/inc/*.h
	rm .clang-format

clean:
	$(MAKE) -C brick_game clean
	rm -rf ../build