#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "snake_game.h"

int main(){
	printf("------------------\n      GAMES\n------------------\n\n");


	int game;
	while (1) {
		printf("Type the number of the game that you want to play: \n");
		printf("Snake game - 1\nExit - 2\n");
		printf("Enter: ");
		scanf_s("%d", &game);
		switch (game)
		{
		case 1:
			system("cls");
			snake();
		default:
			return 0;
		}
	}
}
