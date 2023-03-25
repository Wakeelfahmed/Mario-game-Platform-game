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

//void drawEnemy(Entity* enemy) {
//	// Draw the enemy on the screen
//	drawTexture(enemy->texture, enemy->x, enemy->y, enemy->w, enemy->h);
//}

//#include<stdbool.h>
//typedef struct {
//    int x, y; // position
//    int speed; // movement speed
//    int health; // enemy health
//} Enemy;
//
//Enemy enemies[5];
//#define MAX_ENEMIES 10
//Enemy enemies[MAX_ENEMIES];
//int numEnemies = 0; // number of enemies currently in the game
//
//
//#define ENEMY_SPEED 4
//#define ENEMY_WIDTH 50
//#define ENEMY_HEIGHT 50
//#define ENEMY_MAX_X (SCREEN_WIDTH - ENEMY_WIDTH)
//#define ENEMY_MAX_Y (SCREEN_HEIGHT - ENEMY_HEIGHT)
//
//static SDL_Rect enemy_rect;
//static bool enemy_active = false;
//
//void enemy_init()
//{
//    enemy_rect.w = ENEMY_WIDTH;
//    enemy_rect.h = ENEMY_HEIGHT;
//    enemy_rect.x = 0;
//    enemy_rect.y = 0;
//}
//
//void enemy_spawn()
//{
//    enemy_rect.x = rand() % ENEMY_MAX_X;
//    enemy_rect.y = rand() % ENEMY_MAX_Y;
//    enemy_active = true;
//}
//
//void enemy_move()
//{
//    if (!enemy_active) {
//        return;
//    }
//
//    if (enemy_rect.x < game_get_player_x()) {
//        enemy_rect.x += ENEMY_SPEED;
//    }
//    else {
//        enemy_rect.x -= ENEMY_SPEED;
//    }
//
//    if (enemy_rect.y < game_get_player_y()) {
//        enemy_rect.y += ENEMY_SPEED;
//    }
//    else {
//        enemy_rect.y -= ENEMY_SPEED;
//    }
//
//    if (enemy_rect.x < 0) {
//        enemy_rect.x = 0;
//    }
//    else if (enemy_rect.x > ENEMY_MAX_X) {
//        enemy_rect.x = ENEMY_MAX_X;
//    }
//
//    if (enemy_rect.y < 0) {
//        enemy_rect.y = 0;
//    }
//    else if (enemy_rect.y > ENEMY_MAX_Y) {
//        enemy_rect.y = ENEMY_MAX_Y;
//    }
//}
//
//void enemy_render(SDL_Renderer* renderer)
//{
//    if (!enemy_active) {
//        return;
//    }
//
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    SDL_RenderFillRect(renderer, &enemy_rect);
//}
//
//void enemy_cleanup()
//{
//    enemy_active = false;
//}
