#include "common.h"
static SDL_Texture* pete[3];
void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;
	player->health = 1;
	player->Lives = 3;
	pete[0] = loadTexture("gfx/pete01.png");
	pete[1] = loadTexture("gfx/pete02.png");
	pete[2] = loadTexture("gfx/pete_No_motion.png");
	player->texture = pete[0];
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}
void doPlayer(void)
{
	player->dx = 0;

	if (app.keyboard[SDL_SCANCODE_A])
	{
		if (Speed_Powerup_on)
			player->dx = -11;
		else
			player->dx = -6;
		//player->dx = -PLAYER_MOVE_SPEED;
		player->texture = pete[1];
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		if (Speed_Powerup_on)
			player->dx = 11;
		else
			player->dx = 6;
		player->texture = pete[0];
	}
	if (app.keyboard[SDL_SCANCODE_I] && player->isOnGround)
	{
		player->riding = NULL;
		if (Jump_Powerup_on)
			player->dy = -30; //for more jump
		else
			player->dy = -20;
		//player->dy = Player_Jump_setting;
		playSound(SND_JUMP, CH_PLAYER);
	}
	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		player->x = player->y = 0;
		app.keyboard[SDL_SCANCODE_SPACE] = 0;
	}
}
