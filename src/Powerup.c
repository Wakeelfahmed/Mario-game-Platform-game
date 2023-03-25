#include"common.h"
static void tick(void);
static void touch(Entity* other);
void initPowerup(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

	e->texture = loadTexture("gfx/PowerUp.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;
}
static void tick(void)
{
	self->value += 0.1;

	self->y += sin(self->value);
}
static void touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;

		if (stage.pizzaFound == stage.pizzaTotal)
		{
			playSound(SND_PIZZA_DONE, CH_PIZZA);
			exit(1);
		}
		else
		{
			playSound(SND_PIZZA, CH_PIZZA);
		}
	}
}