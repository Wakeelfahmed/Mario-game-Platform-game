#include"common.h"
#include<stdbool.h>
static void tick(void);
static void touch(Entity* other);
void init_Jump_Powerup(char* line);
void init_Speed_Powerup(char* line);
static void Jump_touch(Entity* other);
static void Speed_touch(Entity* other);


void init_Speed_Powerup(char* line)
{
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->health = 1;
	e->texture = loadTexture("gfx/Jump_PowerUp.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = Speed_touch;
}
void init_Jump_Powerup(char* line)
{
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->health = 1;
	e->texture = loadTexture("gfx/Jump_PowerUp.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = Jump_touch;
}
static void tick(void)
{
	self->value += 0.1;
	self->y += sin(self->value);
}
static void Jump_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
 		self->health = 0;
		Jump_Powerup_on = 1;
		Jump_PowerUp_start = time(NULL);
		playSound(SND_PIZZA, CH_PIZZA);
	}
}
static void Speed_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		Speed_PowerUp_on = 1;
		Speed_PowerUp_start = time(NULL);
		playSound(SND_PIZZA, CH_PIZZA);
	}
}