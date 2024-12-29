#include <SDL2/SDL.h>
#include <stdio.h>
#include <malloc.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "Application"
#define TRUE 1
#define FALSE 0

#define RECT_SIDE 20
#define RECT_X(x) x/RECT_SIDE*RECT_SIDE
#define RECT_Y(y) y/RECT_SIDE*RECT_SIDE

#define WHITE_COLOR 255, 255, 255, 255
#define RED_COLOR 255, 0, 0, 255
#define BLUE_COLOR 0, 255, 0, 255
#define GREEN_COLOR 0, 0, 255, 255

typedef struct
{
	int r, g, b, a;
} Color;

int object_width = SCREEN_HEIGHT/RECT_SIDE;
int object_height = SCREEN_WIDTH/RECT_SIDE;

char **screen_map;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int game_is_running = TRUE;
SDL_Rect *rects;
int rect_count = 0;

Color color = {BLUE_COLOR};
int color_sequence = 0;
Color colors[3] = {{RED_COLOR}, {GREEN_COLOR}, {BLUE_COLOR}};


int init_all(void)
{
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "SDL initialization error");
		return FALSE;
	}

	window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_BORDERLESS 
	);

	if(!window)
	{
		fprintf(stderr, "Window creation error\n");
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window, -1 , 0);

	if(!renderer)
	{
		fprintf(stderr, "Renderer creation error\n");
		return FALSE;
	}

	return TRUE;
}

void setup(void)
{
	rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * SCREEN_WIDTH*SCREEN_HEIGHT/RECT_SIDE/RECT_SIDE);

	screen_map = (char**)malloc(sizeof(char*) * SCREEN_HEIGHT/RECT_SIDE);
	for (int i = 0; i < SCREEN_HEIGHT/RECT_SIDE; i++)
	{
		screen_map[i] = (char*)malloc(SCREEN_WIDTH/RECT_SIDE);
		for(int j = 0; j < SCREEN_WIDTH/RECT_SIDE; j++)
		{
			screen_map[i][j] = FALSE;
		}
	}
}

void clean_screen(void)
{
	for (int i = 0; i < SCREEN_HEIGHT/RECT_SIDE; i++)
	{
		for(int j = 0; j < SCREEN_WIDTH/RECT_SIDE; j++)
		{
			screen_map[i][j] = FALSE;
		}
	}
}

void createRect(int x, int y)
{
	SDL_Rect rect = {RECT_X(x), RECT_Y(y), RECT_SIDE, RECT_SIDE};
	SDL_SetRenderDrawColor(renderer, WHITE_COLOR);
	rects[rect_count++] = rect;
}

void drawRect(void)
{	
	SDL_SetRenderDrawColor(renderer, WHITE_COLOR);
	SDL_RenderFillRects(renderer, rects, rect_count);
	SDL_RenderPresent(renderer);
}

void process_input(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				game_is_running = FALSE;
			else if(event.key.keysym.sym == SDLK_c)
				color = colors[++color_sequence % 3];
			else if(event.key.keysym.sym == SDLK_x)
			{
				clean_screen();
				rect_count = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			int mouse_x = event.motion.x;
			int mouse_y = event.motion.y;
			if(event.motion.state != 0)
			{
				if(screen_map[mouse_y/RECT_SIDE][mouse_x/RECT_SIDE] == FALSE)
				{
					SDL_Rect rect = {RECT_X(mouse_x), RECT_Y(mouse_y), RECT_SIDE, RECT_SIDE};
					screen_map[mouse_y/RECT_SIDE][mouse_x/RECT_SIDE] = TRUE;
					rects[rect_count++] = rect;
				}
			}
	}


}

void update()
{

}

void render(void)
{
	// Color Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw rects
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRects(renderer, rects, rect_count);


	SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	free(rects);
	for(int i = 0; i < SCREEN_HEIGHT/RECT_SIDE; i++)
	{
		free(screen_map[i]);
	}
	free(screen_map);
	SDL_Quit();
}


int main(int argc, char** argv){

	game_is_running = init_all();

	setup();

	while(game_is_running)
	{
		process_input();
		update();
		render();

		SDL_Delay(2);
	}

	destroy_window();

	return 0;
}