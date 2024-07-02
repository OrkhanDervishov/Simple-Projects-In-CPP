#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <time.h>
#include "game.h"
#include "draw_man.h"

#define MAX_WORD_LEN 64

void gameOver(Man *man, int state) {

	system("cls");

	if (state == 1) {
		happyMan(man);
	}
	
	draw(man);
	printf("\n\n%s\n\n", state > 0 ? "You won. HAPPY MAN :)" : "You lost. DEAD MAN ;(");
	exit(0);
}

void make_mistake(Man *man) {
	man->mistakes++;
	addPart(man);

	if (man->mistakes >= 10) {
		gameOver(man, -1);
	}
}

void checkWord(Man *man, char* puzzle_word) {

	int unknown_letters = 0;

	for (int i = 0; i < strlen(puzzle_word); i++) {

		if (puzzle_word[i] == '_') unknown_letters++;
	}

	if (unknown_letters > 0) {
		printf("You have some letters unveil");
		return;
	}
	else {
		printf("There is no unknown letters left");
		gameOver(man, 1);
	}
}

int changeLetter(char *word, char *puzzle_word, char letter) {

	int changed_letters = 0;

	for (int i = 0; i < strlen(word); i++) {


		if (letter == word[i]) {
			puzzle_word[i] = letter;
			changed_letters++;
		}
	}

	return changed_letters > 0 ? 1 : 0;
}

void startHintLetters(char* word, char* puzzle_word) {

	int len = strlen(word);
	int hints = len / 7;
	hints = hints > 0 ? hints : 1;

	while (hints--) {

		int rand_num = rand() % len;
		char letter = word[rand_num];

		changeLetter(word, puzzle_word, letter);
	}

}

int guessLetter(char* word, char* puzzle_word) {

	char ch = '1';

	printf("Guess letter: ");
	scanf(" %c", &ch);

	ch = tolower(ch);

	if (changeLetter(word, puzzle_word, ch)) {
		return 1;
	}
	return 0;
}

void game(Man *man) {

	srand(time(NULL));

	char word[MAX_WORD_LEN];
	char puzzle_word[MAX_WORD_LEN];

	printf("Enter word(max 64 symbols): ");
	scanf("%s", word);

	for (int i = 0; i < strlen(word); i++) {
		word[i] = tolower(word[i]);
	}

	memset(puzzle_word, '_', strlen(word));
	puzzle_word[strlen(word)] = '\0';


	startHintLetters(word, puzzle_word);
	system("cls");
	checkWord(man, puzzle_word);

	while (1) {

		draw(man);
		printf("\n\n%s\n", puzzle_word);

		if (guessLetter(word, puzzle_word) == 0) {
			make_mistake(man);
		}
		checkWord(man, puzzle_word);

		system("cls");
	}
}