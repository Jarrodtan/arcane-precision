#pragma once
#include "cprocessing.h"
struct player {
    CP_Vector position;
    float diameter;
    int direction;
    int active;
    float moveSpeed;
    int lives;
    float manaBuildSpeed;
    float cooldownSpeed;
    float attackDamage;
    float attackSize;
    float attackSpeed;
    float invincibilityTimer;      // Tracks remaining invincibility time
    float invincibilityDuration;  // Duration of invincibility (e.g., 1.5 seconds)
    int score;
};

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);