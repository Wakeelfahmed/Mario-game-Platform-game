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
#include "common.h"
#include"SDL2/SDL_ttf.h"
static void logic(void);
static void draw(void);
static void drawHud(void);
void initStage(short Map_Number)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	memset(&stage, 0, sizeof(Stage));
	stage.entityTail = &stage.entityHead;
	initEntities(Map_Number);
	initPlayer();
	initMap(Map_Number);
}
static void logic(void)
{
	doPlayer();
	doEntities();
	doCamera();
}
static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 0, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);
	drawMap();
	drawEntities();
	drawHud();
}
static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH / 2, 5, 255, 255, 255, TEXT_RIGHT, "TIMER %d", stage.Timer_set - stage.elapsed);
	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "PIZZA %d/%d", stage.pizzaFound, stage.pizzaTotal);

	TTF_Init();

	int heart_x = 10;

	TTF_Font* font = TTF_OpenFont("arial.ttf", 24);

	char heart[] = "\xE2\x9D\xA4";
	int heartSize = 24; // size of each heart in pixels
	int padding = 5; // padding between hearts
	int lives = 3; // number of lives

	if (!font)
		drawText(5, 2, 255, 0, 0, 1, "NOT found");

	SDL_Color color = { 56, 255, 255 };
	const char* text = u8"\u2665"; // Unicode code point for heart symbol
	for (int i = 0; i < player->Lives; i++) {
		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, surface);
		SDL_Rect dstrect = { heart_x, 10, surface->w, surface->h };
		heart_x += 20;
		SDL_RenderCopy(app.renderer, texture, NULL, &dstrect);
		SDL_DestroyTexture(texture);
	}
	TTF_CloseFont(font);

}
