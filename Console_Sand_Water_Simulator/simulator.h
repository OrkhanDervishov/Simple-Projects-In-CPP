#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>


#define MAX_X 128
#define MAX_Y 128
#define MAX_PARTS 1024


enum Type {
	SAND = '@',
	WATER = '.',
	OIL,
	TOTAL_TYPES = 2
};

typedef struct {
	int x;
	int y;
} Position;


typedef struct {
	char arr[MAX_Y][MAX_X];
	int X;
	int Y;
} Image;


typedef struct {
	Position pos;
	Type type;
} Particle;


typedef struct {
	Position pos;
} Summoner;


void display(Image* image, Summoner* summoner, Particle** particleArr, int totalParts, Type genType);


void moveParts(Image* image, Particle** particleArr, size_t totalParts);

void moveSandPart(Image* image, Particle* particle);

void moveWaterPart(Image* image, Particle* particle);


Particle* createPart(int x, int y, Type type);

void readImage(const char* filename, Image* image);

int Simulate();