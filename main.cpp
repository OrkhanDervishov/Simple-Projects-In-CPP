#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "dog_game.h"
#include "snake_game.h"
#include "test.h"

int main(){
	printf("------------------\n      GAMES\n------------------\n\n");


	int game;
	while (1) {
		printf("Type the number of the game that you want to play: \n");
		printf("Hungry Dog - 1\nSnake game - 2\nExit - 3\n");
		printf("Enter: ");
		scanf_s("%d", &game);
		switch (game)
		{
		case 1:
			system("cls");
			dog_game();
		case 2:
			system("cls");
			snake();
		case 3:
			return 0;
		}
	}
}