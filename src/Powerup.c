#include"common.h"
#include<stdbool.h>
static void tick(void)
{
	self->value += 0.01;
	self->y += sin(self->value);
}
static void Enemy_tick(void)
{
	if (abs(self->x - self->sx) < PLATFORM_SPEED && abs(self->y - self->sy) < PLATFORM_SPEED)
	{
		calcSlope(self->ex, self->ey, self->x, self->y, &self->dx, &self->dy);

		self->dx *= PLATFORM_SPEED;
		self->dy *= PLATFORM_SPEED;
	}

	if (abs(self->x - self->ex) < PLATFORM_SPEED && abs(self->y - self->ey) < PLATFORM_SPEED)
	{
		calcSlope(self->sx, self->sy, self->x, self->y, &self->dx, &self->dy);

		self->dx *= PLATFORM_SPEED;
		self->dy *= PLATFORM_SPEED;
	}
}
static void Enemy_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		player->Lives--;
		playSound(SND_PIZZA, CH_PIZZA);
	}
}
void initEnemyPlatform(char* line)
{
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f %f %f", &e->sx, &e->sy, &e->ex, &e->ey);
	e->health = 1;
	e->x = e->sx;
	e->y = e->sy;
	e->tick = Enemy_tick;
	e->texture = loadTexture("gfx/Enemy_No_motion.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_SOLID + EF_WEIGHTLESS + EF_PUSH;
	e->touch = Enemy_touch;
}
//static void Enenmy_tick(void)
//{
//	static short temp;
//	temp = self->dx;
//	self->value += 0.01;
//	if (temp == (self->dx))
//		self->texture = loadTexture("gfx/Enemy_No_motion.png");
//	else if (temp < (self->dx))
//		self->texture = loadTexture("gfx/Enemy_right.png");
//	else if (temp > (self->dx))
//		self->texture = loadTexture("gfx/Enemy_left.png");
//	self->dx += 1 * cos(self->value);
//}

//void init_Enemy(char* line)
//{
//	Entity* e;
//	e = malloc(sizeof(Entity));
//	memset(e, 0, sizeof(Entity));
//	stage.entityTail->next = e;
//	stage.entityTail = e;
//	sscanf(line, "%*s %f %f", &e->x, &e->y);
//	e->health = 1;
//	e->Entity_Code = 1;
//	e->texture = loadTexture("gfx/Enemy01.png");
//	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
//	e->flags = EF_WEIGHTLESS;
//	e->tick = Enemy_tick;
//	e->touch = Enemy_touch;
//}
static void Time_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		stage.start += 5;
		playSound(SND_PIZZA, CH_PIZZA);
	}
}
static void Jump_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		Jump_Powerup_on = 1;
		Jump_Powerup_start = time(NULL);
		playSound(SND_PIZZA, CH_PIZZA);
	}
}
static void Speed_touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		Speed_Powerup_on = 1;
		Speed_Powerup_start = time(NULL);
		playSound(SND_PIZZA, CH_PIZZA);
	}
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
	e->Entity_Code = 0;
	strcpy(e->Entity_name, "Jump");
	e->texture = loadTexture("gfx/Jump_PowerUp.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = Jump_touch;
}
void init_Speed_Powerup(char* line)
{
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->health = 1;
	e->Entity_Code = 1;
	e->texture = loadTexture("gfx/Speed_powerup.png");
	if (!e->texture)
		strcpy(e->Entity_name, "speed");
	strcpy(e->Entity_name, "Speed");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = Speed_touch;
}
void init_Time_Powerup(char* line)
{
	Entity* e;
	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;
	sscanf(line, "%*s %f %f", &e->x, &e->y);
	e->health = 1;
	e->Entity_Code = 1;
	e->texture = loadTexture("gfx/Time_Powerup.png");
	if (!e->texture)
		strcpy(e->Entity_name, "Time");
	strcpy(e->Entity_name, "Time");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = Time_touch;
}