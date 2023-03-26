#include"time.h"
#include "common.h"
#include "stdbool.h"
static void capFrameRate(long* then, float* remainder);
short get_Input_and_Validate_Input(short start, short end) {
	bool input = true; int selection = -1;
	while (input) {
		doInput();
		if (app.keyboard[SDL_SCANCODE_0] == 1) {
			selection = 0;
			app.keyboard[SDL_SCANCODE_0] = 0;
			if (selection >= start && selection <= end) {
				return selection;
			}
		}
		for (int i = 30; i <= 38; i++) {
			if (app.keyboard[i] == 1) {
				// convert the key code to a number and subtract 1 (since the profile array is 0-indexed)
				selection = i - 29;
				app.keyboard[i] = 0;
				// check if the selection is valid
				if (selection >= start && selection <= end) {
					return selection;
				}
			}
		}
	}
}
typedef struct {
	char name[100];
	int score;
	int high_score;
	short Number_of_levels_unlocked;
	int coins;
} Player;
int Player_Profiles_count = -1, Profile_Selected = -1;
Player Player_Profiles[10] = { 0 };

int main()
{
	int loop_iterator = 0;
	for (loop_iterator = 0; loop_iterator < 10; loop_iterator++)
		Player_Profiles[loop_iterator].Number_of_levels_unlocked = 1;
	short Menu_Input, Map_Number = 1;
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
	startTime = SDL_GetTicks();
	then = SDL_GetTicks();
	remainder = 0;
	SDL_Event event;
	SDL_StartTextInput();
	char name[100] = { 0 };
	int name_len = 0;
	bool done = false;
	while (1)
	{

		elapsedTime = SDL_GetTicks() - startTime;
		SDL_SetRenderDrawColor(app.renderer, 0, 75, 0, 255);
		SDL_RenderClear(app.renderer);
		bool optionSelected = false; // variable to keep track if the menu option has been selected
		SDL_RenderClear(app.renderer);
		if (Player_Profiles_count < 0)
			drawText(SCREEN_WIDTH / 2, 70 + 29, 185, 185, 185, 1, "1. Select Profile");
		else
			drawText(SCREEN_WIDTH / 2, 70 + 29, 255, 255, 255, 1, "1. Select Profile");
		drawText(SCREEN_WIDTH / 2, 70 + 29 + 29, 255, 255, 255, 1, "2. CREATE PROFILE");
		drawText(SCREEN_WIDTH / 2, 70 + 29 + 29 + 29, 255, 255, 255, 1, "3. Instructions");
		SDL_RenderPresent(app.renderer);
		if (Player_Profiles_count < 0)
			Menu_Input = get_Input_and_Validate_Input(2, 3);
		else
			Menu_Input = get_Input_and_Validate_Input(1, 3);
		switch (Menu_Input)
		{
		case 1:
		{
			SDL_RenderClear(app.renderer);
			drawText(SCREEN_WIDTH / 2, 45, 255, 255, 255, 1, "Select Profile");
			y = 90;
			for (loop_iterator = 0; loop_iterator <= Player_Profiles_count; loop_iterator++)
			{
				char filename[100]; // allocate a buffer to hold the filename
				sprintf(filename, "%d%s%s", loop_iterator, ". ", Player_Profiles[loop_iterator].name); // format the filename string using sprintf
				drawText(SCREEN_WIDTH / 2, y, 255, 255, 255, 1, filename);
				y += GLYPH_HEIGHT;
			}
			SDL_RenderPresent(app.renderer);
			Menu_Input = -1; // initialize selection to an invalid value
			Menu_Input = get_Input_and_Validate_Input(0, Player_Profiles_count);
			Profile_Selected = Menu_Input;
			SDL_RenderClear(app.renderer);
			drawText(SCREEN_WIDTH / 2, 30, 255, 255, 255, 1, "Select Level");
			y = 90;
			for (int i = 1; i < 3; i++)
			{
				if (i <= Player_Profiles[Profile_Selected].Number_of_levels_unlocked)
					drawText(SCREEN_WIDTH / 2, y, 255, 255, 255, 1, "Level %d", i);
				else
					drawText(SCREEN_WIDTH / 2, y, 185, 185, 185, 1, "Level %d", i);
				y += GLYPH_HEIGHT;
			}
			SDL_RenderPresent(app.renderer);
			Map_Number = get_Input_and_Validate_Input(1, Player_Profiles[Profile_Selected].Number_of_levels_unlocked);
			//short Lives_Temp = 3, Pizzas_Collected_Temp;
		Restart:
			atexit(cleanup);
			initGame();
			initStage(Map_Number);
			stage.Timer_set = 20;
			then = SDL_GetTicks();
			stage.start = time(NULL);
			remainder = 0;
			//player->Lives = Lives_Temp;
			while (1)
			{
				if (app.keyboard[SDL_SCANCODE_ESCAPE] == 1) {
					app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
					break;
				}

				if (stage.completed) {
					if (Map_Number == 2)
						Map_Number = 1;
					Map_Number++;
					Player_Profiles[Profile_Selected].Number_of_levels_unlocked = Map_Number;
					Player_Profiles[Profile_Selected].coins = player->Lives * 2;
					stage.completed = 0;
					goto Restart;
				}
				short temp_x = player->dx;
				if (temp_x == player->dx)
					player->texture = loadTexture("gfx/pete_No_motion.png");
				else if (temp_x == player->dx)
					player->texture = loadTexture("gfx/pete_01.png");
				else if (temp_x == player->dx)
					player->texture = loadTexture("gfx/pete_02.png");

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
					--player->Lives;
					//Lives_Temp = --player->Lives;
				}
				if (Jump_Powerup_on)
				{
					if (stage.end - Jump_Powerup_start >= 9)
						Jump_Powerup_on = 0;
				}
				else if (Speed_Powerup_on) {
					if (stage.end - Speed_Powerup_start >= 9)
						Speed_Powerup_on = 0;

				}
			}
			break;
		}
		case 2:
		{
			SDL_RenderClear(app.renderer);
			drawText(SCREEN_WIDTH / 2, 60, 255, 255, 255, 1, "ENTER YOUR NAME");
			SDL_RenderPresent(app.renderer);
			done = false;
			Player_Profiles_count++;
			while (!done) {
				//SDL_Event event;
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_QUIT:
						done = 1;
						//Player_Profiles_count--;
						break;
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_RETURN) {
							done = 1;
							name_len = 0;
							break;
						}
						else if (event.key.keysym.sym == SDLK_BACKSPACE && name_len > 0) {
							Player_Profiles[Player_Profiles_count].name[name_len - 1] = '\0';
							name_len--;
							SDL_Rect clearRect = { 0, 100, SCREEN_WIDTH, GLYPH_HEIGHT };
							SDL_RenderFillRect(app.renderer, &clearRect);
							drawText(SCREEN_WIDTH / 2, 100, 255, 255, 255, 1, Player_Profiles[Player_Profiles_count].name);
							SDL_RenderPresent(app.renderer);
						}
						break;
					case SDL_TEXTINPUT:
						optionSelected = 1;
						if (name_len < 99 && optionSelected) {
							strcat(Player_Profiles[Player_Profiles_count].name, event.text.text);
							name_len++;
							SDL_Rect clearRect = { 0, 100, SCREEN_WIDTH, GLYPH_HEIGHT };
							SDL_RenderFillRect(app.renderer, &clearRect);
							drawText(SCREEN_WIDTH / 2, 100, 255, 255, 255, 1, Player_Profiles[Player_Profiles_count].name);
							SDL_RenderPresent(app.renderer);
						}
						//optionSelected = 1;
						break;
					}
				}
			}
			break;
		}
		case 3:
		case SDLK_3:
			SDL_RenderClear(app.renderer);
			drawText(SCREEN_WIDTH / 2, 32, 255, 255, 255, 1, "\'A\' - Left");
			drawText(SCREEN_WIDTH / 2, 32 + 29, 255, 255, 255, 1, "\'D\' - Right");
			drawText(SCREEN_WIDTH / 2, 32 + 29 + 29, 255, 255, 255, 1, "\'I\' - Jump");
			drawText(SCREEN_WIDTH / 2, 32 + 29 + 29 + 29, 255, 255, 255, 1, "\'Space bar\' - Restart");
			drawText(SCREEN_WIDTH / 2, 50 + 29 + 29 + 29 + 29, 255, 255, 255, 1, "Press 0 key to exit");
			SDL_RenderPresent(app.renderer);
			while (get_Input_and_Validate_Input(0, 0)) {}
			break;
		case SDLK_ESCAPE:
			exit(0);
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