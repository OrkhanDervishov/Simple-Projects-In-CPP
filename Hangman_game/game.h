#pragma once
#include "draw_man.h"

#define MAX_MISTAKES 10

void gameOver(Man* man, int state);

void make_mistake(Man *man);

void checkWord(Man* man, char* puzzle_word);

int changeLetter(char* word, char* puzzle_word, char letter);

void startHintLetters(char* word, char* puzzle_word);

int guessLetter(char* word, char* puzzle_word);

void game(Man *man);