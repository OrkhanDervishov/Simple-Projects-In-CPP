#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "draw_man.h"

void draw(Man *man) {

	for (int i = 0; i < MAN_Y; i++) {
		printf("%s", man->man_image[i]);
	}
}

void readFile(char* fname, Man *man) {

	FILE* file = fopen(fname, "r");
	char ch;
	int i = 0;
	int j = 0;

	if (file == NULL) {
		printf("Error opening file\n");
		exit(0);
	}

	char buffer[MAN_X];

	for (int i = 0; fgets(buffer, MAN_X, file) != NULL; i++) {

		strcpy(man->man_image[i], buffer);
	}
}

void addPart(Man *man) {

	FILE* file;

	switch (man->mistakes)
	{
	case 1:
		readFile((char*)"man0.txt", man);
		break;
	case 2:
		readFile((char*)"man1.txt", man);
		break;
	case 3:
		readFile((char*)"man2.txt", man);
		break;
	case 4:
		readFile((char*)"man3.txt", man);
		break;
	case 5:
		readFile((char*)"man4.txt", man);
		break;
	case 6:
		readFile((char*)"man5.txt", man);
		break;
	case 7:
		readFile((char*)"man6.txt", man);
		break;
	case 8:
		readFile((char*)"man7.txt", man);
		break;
	case 9:
		readFile((char*)"man8.txt", man);
		break;
	case 10:
		readFile((char*)"man9.txt", man);
		break;
	default:
		break;
	}
}

void happyMan(Man *man) {
	initMan(man);
	readFile((char*)"happy_man.txt", man);
}



void initMan(Man* man) {
	for (int i = 0; i < MAN_Y; i++) {
		memset(man->man_image[i], ' ', MAN_X - 2);
		man->man_image[i][MAN_X - 2] = '\n';
		man->man_image[i][MAN_X - 1] = '\0';
	}
}