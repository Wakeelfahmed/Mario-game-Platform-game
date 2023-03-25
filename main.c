//#include <string.h>
#include"time.h"
#include "common.h"
#include "stdbool.h"
static void capFrameRate(long* then, float* remainder);

typedef struct {
	char name[100];
	int score;
	int high_score;
} Player;
int Player_Profiles_count = 0;
Player Player_Profiles[10] = { 0 };
int main()
{
	long then;	float remainder;
	int y = 20;
	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	int startTime, elapsedTime;
	int menuChoice = 0; // The player's menu choice
	// Initialize SDL and the game state
	initSDL();
	atexit(cleanup);
	initGame();
	//initStage();

	// Start the timer
	startTime = SDL_GetTicks();

	then = SDL_GetTicks();
	remainder = 0;
	SDL_Event event;

	SDL_StartTextInput();
	char name[100] = { 0 };
	int name_len = 0;
	bool done = false;  int loop_iterator = 0;
	while (1)
	{
		// Get the elapsed time since the game started
		elapsedTime = SDL_GetTicks() - startTime;

		// Clear the screen
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);

		//SDL_RenderClear(app.renderer);
		bool optionSelected = false; // variable to keep track if the menu option has been selected

		// Handle input for the menu
		while (SDL_PollEvent(&event))
		{
			SDL_RenderClear(app.renderer);
			drawText(SCREEN_WIDTH / 2, 32, 255, 255, 255, 1, "1. CREATE PROFILE");
			drawText(SCREEN_WIDTH / 2, 64, 255, 255, 255, 1, "2. Select Profile");
			drawText(SCREEN_WIDTH / 2, 96, 255, 255, 255, 1, "3. QUT GAME");
			SDL_RenderPresent(app.renderer);
			if (event.type == SDL_KEYDOWN)
			{
				SDL_GetScancodeFromKey(event.key.keysym.sym);
				switch (event.key.keysym.sym)
				{
				case SDLK_KP_1:
				case SDLK_1:
					SDL_RenderClear(app.renderer);
					drawText(SCREEN_WIDTH / 2, 30, 255, 255, 255, 1, "ENTER YOUR NAME");
					SDL_RenderPresent(app.renderer);
					done = false;
					while (!done) {
						//SDL_Event event;
						while (SDL_PollEvent(&event)) {
							switch (event.type) {
							case SDL_QUIT:
								done = 1;
								break;
							case SDL_KEYDOWN:
								if (event.key.keysym.sym == SDLK_RETURN) {
									done = 1;
									Player_Profiles_count++;
									name_len = 0;
									break;
								}
								else if (event.key.keysym.sym == SDLK_BACKSPACE && name_len > 0) {
									Player_Profiles[Player_Profiles_count].name[name_len - 1] = '\0';
									name_len--;
									SDL_Rect clearRect = { 0, 60, SCREEN_WIDTH, GLYPH_HEIGHT };
									SDL_RenderFillRect(app.renderer, &clearRect);
									drawText(SCREEN_WIDTH / 2, 60, 255, 255, 255, 1, Player_Profiles[Player_Profiles_count].name);
									SDL_RenderPresent(app.renderer);
								}
								break;
							case SDL_TEXTINPUT:
								if (name_len < 99 && optionSelected) {
									strcat(Player_Profiles[Player_Profiles_count].name, event.text.text);
									name_len++;
									SDL_Rect clearRect = { 0, 60, SCREEN_WIDTH, GLYPH_HEIGHT };
									SDL_RenderFillRect(app.renderer, &clearRect);
									drawText(SCREEN_WIDTH / 2, 60, 255, 255, 255, 1, Player_Profiles[Player_Profiles_count].name);
									SDL_RenderPresent(app.renderer);
								}
								optionSelected = 1;
								break;
							}
						}
					}

					menuChoice = 1;
					break;
				case SDLK_2:
				{
					drawText(SCREEN_WIDTH / 2, 10, 255, 255, 255, 1, "Select Profile");
					y = 25;
					SDL_RenderClear(app.renderer);
					for (loop_iterator = 0; loop_iterator < Player_Profiles_count; loop_iterator++)
					{
						char filename[100]; // allocate a buffer to hold the filename
						sprintf(filename, "%d%s%s", loop_iterator, ". ", Player_Profiles[loop_iterator].name); // format the filename string using sprintf
						drawText(SCREEN_WIDTH / 2, y, 255, 255, 255, 1, filename);
						y += GLYPH_HEIGHT;
					}
					SDL_RenderPresent(app.renderer);
					bool input = true;
					int selection = -1; // initialize selection to an invalid value

					while (input) {
						doInput();
						if (app.keyboard[SDL_SCANCODE_0] == 1) {
							selection = 0;
							app.keyboard[SDL_SCANCODE_0] = 0;
							if (selection >= 0 && selection < Player_Profiles_count) {
								input = false; // exit the loop
							}
							break;
						}
						for (int i = 30; i <= 38; i++) {
							if (app.keyboard[i] == 1) {
								// convert the key code to a number and subtract 1 (since the profile array is 0-indexed)
								selection = i - 29;
								app.keyboard[i] = 0;
								// check if the selection is valid
							}
						}
						if (selection >= 0 && selection < Player_Profiles_count) {
							input = false; // exit the loop
						}
					}
					drawText(SCREEN_WIDTH / 2, 10, 255, 255, 255, 1, "1. Start Game");
					short Lives_Temp = 3, Pizzas_Collected_Temp;
				Restart:
					atexit(cleanup);
					initGame();
					initStage();
					stage.Timer_set = 15;
					then = SDL_GetTicks();
					stage.start = time(NULL);
					remainder = 0;
					//player->Lives = Lives_Temp;
					while (1)
					{
						prepareScene();
						doInput();
						app.delegate.logic();
						app.delegate.draw();
						presentScene();
						capFrameRate(&then, &remainder);
						stage.end = time(NULL);
						stage.elapsed = stage.end - stage.start;
						if (stage.elapsed >= stage.Timer_set) {
							if (player->Lives == 0)
								goto Restart;
							stage.start = time(NULL);
							Lives_Temp = --player->Lives;
							//Pizzas_Collected_Temp = stage.pizzaFound;
						}
						if (Jump_Powerup_on)
						{
							short timetake = stage.end - Jump_PowerUp_start;
							if (stage.end - Jump_PowerUp_start >= 8)
								Jump_Powerup_on = 0;
						}
					}
					break;
				}
				case SDLK_3:
				case SDLK_ESCAPE:
					break;
				}
			}
		}
	}
}
static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;
	if (wait < 1)
	{
		wait = 1;
	}
	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();
}