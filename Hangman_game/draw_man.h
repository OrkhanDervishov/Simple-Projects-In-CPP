#pragma once
#include <stdio.h>

#define MAN_X 22
#define MAN_Y 16

typedef struct {
	int mistakes;
	char man_image[MAN_Y][MAN_X];
} Man;

void initMan(Man *man);

void readFile(char* fname, Man *man);

void addPart(Man *man);

void happyMan(Man* man);

void draw(Man* man);