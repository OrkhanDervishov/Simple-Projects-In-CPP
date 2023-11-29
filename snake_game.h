#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <random>
#include <iostream>
#include <ctime>


typedef struct
{
	int x;
	int y;
} body;


int snake() {
	using namespace std;

	// Intro
	Sleep(200);

	printf("------------------------------\n");
	Sleep(200);

	printf("         SNAKE GAME\n");
	Sleep(200);

	printf("------------------------------\n\n");
	Sleep(250);
	// Defining the size of the map

	int mapsize;
	int width = 14, height = 14;

	printf("Enter the size of the map\n10x10 - 1\n15x15 - 2\n20x20 - 3\n\nEnter there: ");
	cin >> mapsize;


	// Defining the width and the height of the map according to mapsize
	switch (mapsize)
	{
	case 1:
		width = 13;
		height = 13;
		break;
	case 2:
		width = 18;
		height = 18;
		break;
	case 3:
		width = 23;
		height = 23;
		break;
	// if the value of the mapsize is not valid
	default:
		printf("The size that you entered is not valid. The default size is 10x10");
		width = 13;
		height = 13;
		mapsize = 1;
	}
	printf("\n");

	// declaring the parts of the map
	char* corner = new char[width];
	char* middle = new char[width];


	// Defining map part according to mapsize
	switch (mapsize)
	{
	// 10x10 map
	case 1:
		strcpy(corner, "############");
		strcpy(middle, "#          #");
		break;
	// 15x15 map 
	case 2:
		strcpy(corner, "#################");
		strcpy(middle, "#               #");
		break;
	// 20x20 map
	case 3:
		strcpy(corner, "######################");
		strcpy(middle, "#                    #");
	}


	// Declearing required parametres

	/*Declaring the height and the width of the
	* map in the heap
	*/
	char **map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}

	// key is used to store control input
	char key;
	int x = 5, y = 5;

	// The location of the first fruit is predefined and is
	// in x: 3 and y: 3 as default
	int foodx = 3, foody = 3;

	// A variable to count the number of eaten fruits
	int counter = 0;

	/* This variables are used to temporary store
	 the coordinations of parts of the snake's body
	 tempx and tempy are used to store the coordinations
	 where snake's body's first part will move, and 
	 tempx2 and tempy2 are used to store current coordinations
	 for the second part of the body */
	int tempx, tempy; 
	int tempx2, tempy2;

	// Declaring the array that will store parametres 
	// of the parts of snake's body 
	body *snake = new body[(height - 3)*(width - 3) + 1];

	// The first coordinations of snake's head are predefined
	snake[0].x = x, snake[0].y = y;

	// Variable that will store the lenght of the snake's body
	int len = 1;


	// Reading data from from the file
	// This file is used to record the best result
	// record variable is 0, as the record maybe doesn't exist
	freopen("./records/snake_record.txt", "r", stdin);
	int record = 0;
	scanf("%d", &record);


	system("cls");
	
	do {

		// New map generation
		strcpy(map[0], corner);
		strcpy(map[height - 2], corner);
		for (int i = 1; i < height - 2; i++) {
			strcpy(map[i], middle);
		}

		// Snake generation
		map[foody][foodx] = '*';
		map[snake[0].y][snake[0].x] = '@';
		for (int i = 1; i < len; i++) {
			map[snake[i].y][snake[i].x] = '&';
		}

		// Map display
		for (int i = 0; i < height - 1; i++) {
			printf("%s\n", map[i]);
		}
		printf("Count: %d\n", counter);
		printf("Record: %d", record);


		// Controls
		key = _getch();

		system("cls");

		// If key == e while loop will be broken and 
		// program will finish
		map[y][x] = ' ';
		if (key == 'w') y--;
		if (key == 'a') x--;
		if (key == 's') y++;
		if (key == 'd') x++;


		// When snake enters to the wall in one side 
		// it will exit from the wall in the other side
		if (x == width - 2) x = 1;
		if (x == 0) x = width - 3;
		if (y == height - 2) y = 1;
		if (y == 0) y = height - 3;

		// If snake ate the fruit 
		if (y == foody && x == foodx){
			counter++;
			len++;
		}


		// Snake body move
		tempx = x, tempy = y;
		for (int i = 0; i < len; i++) {
			tempx2 = snake[i].x;
			tempy2 = snake[i].y;
			snake[i].x = tempx;
			snake[i].y = tempy;
			tempx = tempx2;
			tempy = tempy2;
		}


		/*If snake ate the fruit, fruit will spawn in
		* random place in the map, but it will not 
		* appear inside the body of snake
		*/
		if (y == foody && x == foodx) {
			bool place = false;

			srand(time(NULL));

			while(place == false){
				for (int t = 0; t <= len; t++) {
					if (foodx == snake[t].x && foody == snake[t].y) {
						foodx = rand() % (width - 3) + 1;
						foody = rand() % (height - 3) + 1;
						break;
					}
					if (t == len) place = true;
				}
			}
		}


		// If snake's body parts touching
		for (int i = 1; i < len; i++) {
			if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) goto end;
		}

	} while (key != 'e');
	end:

	// Declaring total points and the top record
	printf("GAME OVER\n\n");
	Sleep(500);

	printf("You got %d points!\n", counter);

	// If the best result is beaten
	if (counter > record) {
		Sleep(300);
		printf("New Record: %d\n", counter);
		freopen("./records/snake_record.txt", "w", stdout);
		printf("%d", counter);
	}

	// Deleting the array from the heap and finishing the program
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map, corner, middle, snake;

	return 0;
}
