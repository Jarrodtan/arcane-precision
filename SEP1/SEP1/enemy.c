#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include "utils.h"
#include "game.h"
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_BULLETS 100  // Maximum bullets in array

extern float dt;
extern int roomsPassed;
extern struct player player;

struct enemy {
	CP_Vector position;
	float diameter;
	float speed;
	CP_Vector direction;
	int lives;
	int active;
};

struct enemyAttack {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	int damage;
	float speed;
	int active;
};

float difficulty = 1;
CP_Vector bulletMoveD;
CP_Vector bulletMoveN;
CP_Vector enemyMoveD;
CP_Vector enemyMoveN;

struct enemy enemyStationary;
struct enemy enemyMelee;
struct enemyAttack bullets[MAX_BULLETS]; // Array of bullets

void initialize_bullet(struct enemyAttack* bullet, CP_Vector position, CP_Vector direction, float speed, int damage) {
	bullet->position = position;
	bullet->direction = direction;
	bullet->speed = speed;
	bullet->damage = damage;
	bullet->diameter = 30; // Set diameter for each bullet
	bullet->active = 1;    // Mark bullet as active
}

void enemy_code() {
	static float shootTimer = 0.0f;
	if (roomsPassed % 5 == 0) {
		difficulty = (roomsPassed / 5) + 1.0;
	}
	// Initialize enemy properties
	enemyStationary.lives = 1 + difficulty;
	enemyStationary.diameter = 50;
	enemyStationary.position = CP_Vector_Set(WINDOW_WIDTH / 1.5f, WINDOW_HEIGHT / 2.0f);
	enemyMelee.lives = 2 + difficulty;
	enemyMelee.diameter = 50;

	// Draw stationary enemy
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(enemyStationary.position.x, enemyStationary.position.y, enemyStationary.diameter);

	// Update shooting timer
	shootTimer += dt * difficulty;

	// Check if 5 seconds have passed to shoot
	if (shootTimer >= 5.0f) {
		shootTimer = 0.0f;

		// Calculate bullet direction towards player
		bulletMoveD.x = player.position.x - enemyStationary.position.x;
		bulletMoveD.y = player.position.y - enemyStationary.position.y;
		bulletMoveN = CP_Vector_Normalize(bulletMoveD);

		// Find an available bullet slot in the array
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!bullets[i].active) {
				// Initialize new bullet
				initialize_bullet(&bullets[i], enemyStationary.position, CP_Vector_Scale(bulletMoveN, difficulty), 400.0f, 1);
				break;
			}
		}
	}

	// Update and draw all active bullets
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bullets[i].active) {
			// Move bullet
			bullets[i].position = CP_Vector_Add(bullets[i].position, CP_Vector_Scale(bullets[i].direction, bullets[i].speed * dt));

			// Draw bullet
			CP_Settings_Fill(CP_Color_Create(242, 103, 75, 255));
			CP_Graphics_DrawCircle(bullets[i].position.x, bullets[i].position.y, bullets[i].diameter);

			// Check for collision with player
			if (AreCirclesIntersecting(player.position.x, player.position.y, player.diameter, bullets[i].position.x, bullets[i].position.y, bullets[i].diameter) == 1) {
				take_damage(&player, bullets[i].damage);
				bullets[i].active = 0; // Deactivate bullet upon collision
			}

			// Deactivate bullet if it goes off-screen
			if (bullets[i].position.x < 10 || bullets[i].position.x > WINDOW_WIDTH-10 ||
				bullets[i].position.y < 10 || bullets[i].position.y > WINDOW_HEIGHT-10) {
				bullets[i].active = 0;
			}
		}
	}

	// Enemy movement logic for melee enemy (similar to stationary)
	enemyMelee.speed = 10.0f * difficulty;
	enemyMoveD.x = player.position.x - enemyMelee.position.x;
	enemyMoveD.y = player.position.y - enemyMelee.position.y;
	enemyMoveN = CP_Vector_Normalize(enemyMoveD);

	enemyMelee.direction.x = (enemyMoveN.x * 5) + (rand() % 3 - 1);  // Add randomness to movement
	enemyMelee.direction.y = (enemyMoveN.y * 5) + (rand() % 3 - 1);

	// Update melee enemy position
	enemyMelee.position = CP_Vector_Add(enemyMelee.position, CP_Vector_Scale(enemyMelee.direction, enemyMelee.speed * dt));
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyMelee.position.x, enemyMelee.position.y, enemyMelee.diameter);

	// Collision and damage logic for melee enemy
	if (CP_Vector_Distance(player.position, enemyMelee.position) <= (player.diameter / 2) + (enemyMelee.diameter / 2)) {
		take_damage(&player, 1);
	}

	//enemy takes dmg when in contact with player attack
	if (AreCirclesIntersecting(enemyMelee.position.x, enemyMelee.position.y, enemyMelee.diameter, playerAttack.position.x, playerAttack.position.y, playerAttack.diameter) == 1)
	{
		//take_damage(&enemy, playerAttack.damage);
		enemyMelee.lives -= playerAttack.damage;
		//despawn player attack projectile
		
	}
	if (AreCirclesIntersecting(enemyStationary.position.x, enemyStationary.position.y, enemyStationary.diameter, playerAttack.position.x, playerAttack.position.y, playerAttack.diameter) == 1)
	{
		//take_damage(&enemy, playerAttack.damage);
		enemyStationary.lives -= playerAttack.damage;
		//despawn player attack projectile
		
	}

}
