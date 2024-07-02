#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"
#include "draw_man.h"

int main() {

	Man* man = new Man;
	man->mistakes = 0;
	initMan(man);

	game(man);

	delete man;
}