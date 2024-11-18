#pragma once
#define MAX_BULLETS 100  // Maximum bullets in array
#define MAX_ENEMIES 100  // Maximum enemies in array
#include <stdbool.h>

struct enemyAttack {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float speed;
	int damage;
	int active;

};

struct enemy {
	int type;
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float speed;
	int lives;
	int active;
	float shootTimer;
	struct enemyAttack bullets[MAX_BULLETS];
	bool isFrozen;
	float freezeTimer;
};

void init_enemy(void);
void enemy_code(void);
void take_damage(struct player* p, int damage);
