#include"common.h"

//Entity Enemy;

static SDL_Texture* Enemy_Texture[2];

void initEnemy(void)
{
	Enemy = malloc(sizeof(Entity));
	memset(Enemy, 0, sizeof(Entity));
	stage.entityTail->next = Enemy;
	stage.entityTail = Enemy;
	Enemy->health = 1;
	Enemy->Lives = 3;
	Enemy_Texture[0] = loadTexture("gfx/Enemy01.png");
	Enemy_Texture[1] = loadTexture("gfx/Enemy02.png");
	Enemy->texture = Enemy_Texture[0];
	SDL_QueryTexture(Enemy->texture, NULL, NULL, &Enemy->w, &Enemy->h);
}
