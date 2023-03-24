/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include"time.h"
#include "common.h"
#include "stdbool.h"
static void capFrameRate(long* then, float* remainder);

//char* global_dir = "C:\\Users\\di918039\\source\\repos\\cs1pr-portfolio\\project-visual-studio\\SpringProject";

int main() {
	long then;
	float remainder;

	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

	then = SDL_GetTicks();

	remainder = 0;


	SDL_StartTextInput();
	char name[100] = { 0 };
	int name_len = 0;
	bool done = false;

	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) {
					done = 1;
				}
				else if (event.key.keysym.sym == SDLK_BACKSPACE && name_len > 0) {
					name[name_len - 1] = '\0';
					name_len--;
				}
				break;
			case SDL_TEXTINPUT:
				if (name_len < 99) {
					strcat(name, event.text.text);
					name_len++;
				}
				break;
			}
		}
	}

	time_t start, end;   int Timer_set = 15;
	double elapsed;
	start = time(NULL);
	while (1)
	{
		prepareScene();

		doInput();

		app.delegate.logic();

		app.delegate.draw();

		presentScene();

		capFrameRate(&then, &remainder);
	end = time(NULL);
	elapsed = end - start;
	if (elapsed == Timer_set)
		exit(1);
	}
	printf("Time elapsed: %.2lf seconds\n", elapsed);

	return 0;
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
