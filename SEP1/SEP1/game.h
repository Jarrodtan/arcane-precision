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
    int attackDamage;
    float attackSize;
    float attackSpeed;
    float invincibilityTimer;      // Tracks remaining invincibility time
    float invincibilityDuration;  // Duration of invincibility (e.g., 1.5 seconds)
    int score;
    float hitboxSize;
};

struct manabar {
    float x;
    float y;
    float width;
    float height;
};

struct hearts {
    float x;
    float y;
    float size;
    float spacing;
};

struct playerAttack {
    CP_Vector position;
    float diameter;
    CP_Vector direction;
    int damage;
    float speed;
    int isActive;
    enum Spells selSpell;
};

enum Spells { FIREBALL, ICESHARDS };
extern enum Spells selectedSpell;

void Game_Init(void);
void Game_Update(void);
void Game_Exit(void);
void saveGame(void);
void take_damage(struct player* p, int damage);