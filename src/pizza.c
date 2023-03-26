#include "common.h"

static void tick(void);
static void touch(Entity *other);
void initPizza(char *line)
{
	Entity *e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->health = 1;
	e->Entity_Code = 4;
	strcpy(e->Entity_name, "pizza");
	e->texture = loadTexture("gfx/pizza.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;
	stage.pizzaTotal++;
}
static void tick(void)
{
	self->value += 0.1;
	self->y += sin(self->value);
}
static void touch(Entity *other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		stage.pizzaFound++;
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