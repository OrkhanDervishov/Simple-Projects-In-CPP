#include "simulator.h"



// Display Image
void display(Image* image, Summoner* summoner, Particle** particleArr, int totalParts, Type genType) {

	//srefreshImage(image, imageCopy);

	//Title
	printf("PARTICLE SIMULATOR\n\nGENERATION TYPE - %s\n\n", genType == SAND ? "Sand" : "Water");

	// Simulation image
	image->arr[summoner->pos.y][summoner->pos.x] = '$';

	for (int i = 0; i < image->Y; i++) {
		printf("%s", image->arr[i]);
	}


	// Instructions

	printf("\n\nMove rigth - d\nMove left - a\nSpawn object - s\nChange particle type - w\nSpeed up - z\nSlow down - x\nPause - p\nQuit - q");
}



// Start Moving All Particles
void moveParts(Image* image, Particle** particleArr, size_t totalParts) {

	for (size_t i = 0; i < totalParts; i++) {

		if (particleArr[i]->type == SAND) {
			moveSandPart(image, particleArr[i]);
			continue;
		}
		if (particleArr[i]->type == WATER) {
			moveWaterPart(image, particleArr[i]);
			continue;
		}

	}
}



// Moving Pattern of Water Particle
void moveSandPart(Image* image, Particle* particle) {


	image->arr[particle->pos.y][particle->pos.x] = ' ';

	if (image->arr[particle->pos.y + 1][particle->pos.x] == ' ') {
		image->arr[particle->pos.y][particle->pos.x] = ' ';
		particle->pos.y++;
	}

	else if (image->arr[particle->pos.y + 1][particle->pos.x + 1] == ' ' && image->arr[particle->pos.y + 1][particle->pos.x - 1] == ' ') {
		image->arr[particle->pos.y][particle->pos.x] = ' ';
		particle->pos.y++;
		if (rand() % 2 > 0) particle->pos.x++;
		else particle->pos.x--;
	}
	else if (image->arr[particle->pos.y + 1][particle->pos.x + 1] == ' ') {
		image->arr[particle->pos.y][particle->pos.x] = ' ';
		particle->pos.y++;
		particle->pos.x++;
	}
	else if (image->arr[particle->pos.y + 1][particle->pos.x - 1] == ' ') {
		image->arr[particle->pos.y][particle->pos.x] = ' ';
		particle->pos.y++;
		particle->pos.x--;
	}


	image->arr[particle->pos.y][particle->pos.x] = SAND;
}



// Moving Pattern of Water Particle
void moveWaterPart(Image* image, Particle* particle) {


	image->arr[particle->pos.y][particle->pos.x] = ' ';

	if (image->arr[particle->pos.y + 1][particle->pos.x] == ' ') {
		particle->pos.y++;
	}

	else if (image->arr[particle->pos.y][particle->pos.x + 1] == ' ' && image->arr[particle->pos.y][particle->pos.x + 2] == ' ' && image->arr[particle->pos.y][particle->pos.x - 1] == ' ' && image->arr[particle->pos.y][particle->pos.x - 2] == ' ') {
		if (rand() % 2) particle->pos.x++;
		else particle->pos.x--;
	}

	else if (image->arr[particle->pos.y][particle->pos.x + 1] == ' ' && image->arr[particle->pos.y][particle->pos.x + 2] == ' ' /*&& image->arr[particle->pos.y][particle->pos.x - 1] == '@'*/) {
		particle->pos.x++;
	}
	else if (image->arr[particle->pos.y][particle->pos.x - 1] == ' ' && image->arr[particle->pos.y][particle->pos.x - 2] == ' ' /*&& image->arr[particle->pos.y][particle->pos.x + 1] == '@'*/) {
		particle->pos.x--;
	}

	else if (image->arr[particle->pos.y + 1][particle->pos.x + 1] == ' ' && image->arr[particle->pos.y + 1][particle->pos.x - 1] == ' ') {
		particle->pos.y++;
		if (rand() % 2) particle->pos.x++;
		else particle->pos.x--;
	}
	else if (image->arr[particle->pos.y + 1][particle->pos.x + 1] == ' ') {
		particle->pos.y++;
		particle->pos.x++;
	}
	else if (image->arr[particle->pos.y + 1][particle->pos.x - 1] == ' ') {
		particle->pos.y++;
		particle->pos.x--;
	}

	image->arr[particle->pos.y][particle->pos.x] = WATER;
}




// Create A New Paticle
Particle* createPart(int x, int y, Type type) {
	Particle* particle = new Particle;
	particle->pos.x = x;
	particle->pos.y = y + 1;
	particle->type = type;

	return particle;
}





// Read Image File
void readImage(const char* filename, Image* image) {

	FILE* file;
	char buffer[MAX_X];

	file = fopen(filename, "r");


	for (int i = 0; fgets(buffer, MAX_X, file) != NULL; i++) {
		strcpy(image->arr[i], buffer);
		image->Y = i + 1;
	}
	image->X = strlen(buffer);


	fclose(file);
}




// Start Simulation
int Simulate() {

	Image* image = new Image;
	Summoner* summoner = new Summoner;
	Particle** particleArr = new Particle * [MAX_PARTS];
	Type genType = SAND;
	Type types[] = {SAND, WATER};
	int typeNum = 0;
	size_t totalParts = 0;
	time_t gameSpeed = 80;

	srand(time(NULL));

	readImage("bowl.txt", image);
	//**************************************************
	//MAIN PROGRAM

	summoner->pos.x = image->X / 2;
	summoner->pos.y = 0;


	while (1) {
		Sleep(gameSpeed);
		system("cls");

		display(image, summoner, particleArr, totalParts, genType);


		// Move summoner left
		if (GetKeyState(0x41) & 0x8000) {
			if (summoner->pos.x > 0) {
				image->arr[summoner->pos.y][summoner->pos.x] = ' ';
				summoner->pos.x--;
			}
		}

		// Move summoner rigth
		if (GetKeyState(0x44) & 0x8000) {
			if (summoner->pos.x < image->X - 1) {
				image->arr[summoner->pos.y][summoner->pos.x] = ' ';
				summoner->pos.x++;
			}
		}

		// Switch material
		if (GetKeyState(0x57) & 0x8000) {
			typeNum++;
			genType = types[typeNum % TOTAL_TYPES];
		}

		// Summon particle
		if (GetKeyState(0x53) & 0x8000) {
			particleArr[totalParts] = createPart(summoner->pos.x, summoner->pos.y, genType);
			totalParts++;
		}

		// Pause game
		if (GetKeyState(0x50) & 0x8000) {
			system("pause");
		}

		// Speed up the game
		if (GetKeyState(0x5A) & 0x8000) {
			if (gameSpeed > 20) {
				gameSpeed -= 20;
			}
		}

		// Slow down the game
		if (GetKeyState(0x58) & 0x8000) {
			gameSpeed += 20;
		}

		// Exit
		if (GetKeyState(0x51) & 0x8000) {
			break;
		}


		moveParts(image, particleArr, totalParts);
	}


	for (int i = 0; i < totalParts; i++) {
		delete particleArr[i];
	}
	delete image, summoner;
	delete[] particleArr;
}