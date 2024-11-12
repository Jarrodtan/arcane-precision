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
#define MAX_ENEMIES 100  // Maximum enemies in array

extern float dt;
extern int roomsPassed;
extern struct player player;
extern struct playerAttack playerAttack;

struct enemy {
	int type;
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float speed;
	int lives;
	int active;
};

struct enemyAttack {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float speed;
	int damage;
	int active;
};

float difficulty = 1;
CP_Vector bulletMoveD;
CP_Vector bulletMoveN;
CP_Vector enemyMoveD;
CP_Vector enemyMoveN;

//struct enemy enemyStationary[MAX_ENEMIES];
//struct enemy enemyMelee[MAX_ENEMIES];
struct enemy enemies[MAX_ENEMIES];
struct enemyAttack bullets[MAX_BULLETS]; // Array of bullets

void initialize_bullet(struct enemyAttack* bullet, CP_Vector position, CP_Vector direction, float speed, int damage) {
	bullet->position = position;
	bullet->direction = direction;
	bullet->speed = speed;
	bullet->damage = damage;
	bullet->diameter = 30; // Set diameter for each bullet
	bullet->active = 1;    // Mark bullet as active
}

void initialize_enemyStationary(struct enemy* enemyStationary, CP_Vector position) {
	// Initialize enemy properties
	enemyStationary->type = 1;
	enemyStationary->position = position;
	enemyStationary->diameter = 50;
	//enemyStationary->direction = CP_Vector_Set();
	enemyStationary->speed = 0;
	enemyStationary->lives = 1 + difficulty;
	enemyStationary->active = 1;
}
void initialize_enemyMelee(struct enemy* enemyMelee, CP_Vector position) {
	// Initialize enemy properties
	enemyMelee->type = 2;
	enemyMelee->position = position;
	enemyMelee->diameter = 50;
	//enemyMelee->direction = CP_Vector_Set(0,0);
	enemyMelee->speed = 10.0f * difficulty;
	enemyMelee->lives = 2 + difficulty;
	enemyMelee->active = 1;
}

void enemy_code() {
	static float shootTimer = 0.0f;
	if (roomsPassed % 5 == 0) {
		difficulty = (roomsPassed / 5) + 1.0;
	}

	int enemyNumber = difficulty + 1;

	// Find an available enemy slot in the array
	//for loop enemyNumber
	//generate rng for enemy position
	for (int i = 0; i < enemyNumber; i++) {
		CP_Vector enemyPosition = CP_Vector_Set(CP_Random_RangeInt(1, WINDOW_WIDTH), CP_Random_RangeInt(1, WINDOW_HEIGHT));
		if (enemies[i].active == 0) {
			int enemyType = CP_Random_RangeInt(1, 2);
			if (enemyType == 1) {
				//initialise melee
				initialize_enemyMelee(&enemies[i], enemyPosition);
				break;
			}
			if (enemyType == 2) {
				//initialise stationary
				initialize_enemyStationary(&enemies[i], enemyPosition);
				break;
			}
		}
		
	}
		
	// Update and draw all active enemies
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].active == 1) {

			
			
				
			if (enemies[i].type == 1) { //stationary enemy
				// Draw stationary enemy
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Graphics_DrawCircle(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter);

				//enemy shooting------------------------------------------------------
				// Update shooting timer
				shootTimer += dt * difficulty;

				// Check if 5 seconds have passed to shoot
				if (shootTimer >= 5.0f) {
					shootTimer = 0.0f;

					// Calculate bullet direction towards player
					bulletMoveD.x = player.position.x - enemies[i].position.x;
					bulletMoveD.y = player.position.y - enemies[i].position.y;
					bulletMoveN = CP_Vector_Normalize(bulletMoveD);

					// Find an available bullet slot in the array
					for (int i = 0; i < MAX_BULLETS; i++) {
						if (!bullets[i].active) {
							// Initialize new bullet
							initialize_bullet(&bullets[i], enemies[i].position, CP_Vector_Scale(bulletMoveN, difficulty), 400.0f, 1);
							break;
						}
					}

				}
			}
				
			if (enemies[i].type == 2) { //melee enemy
				//draw melee enemy
				CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
				CP_Graphics_DrawCircle(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter);

				// Enemy movement logic for melee enemy (similar to stationary)
				enemyMoveD.x = player.position.x - enemies[i].position.x;
				enemyMoveD.y = player.position.y - enemies[i].position.y;
				enemyMoveN = CP_Vector_Normalize(enemyMoveD);

				enemies[i].direction.x = (enemyMoveN.x * 5) + (rand() % 3 - 1);  // Add randomness to movement
				enemies[i].direction.y = (enemyMoveN.y * 5) + (rand() % 3 - 1);

				// Update melee enemy position
				enemies[i].position = CP_Vector_Add(enemies[i].position, CP_Vector_Scale(enemies[i].direction, enemies[i].speed * dt));


			}
			


			// Collision and damage logic for when enemy comes in contact with player
			if (CP_Vector_Distance(player.position, enemies[i].position) <= (player.diameter / 2) + (enemies[i].diameter / 2)) {
				take_damage(&player, 1);
			}

			//enemy takes dmg when in contact with player attack
			if (AreCirclesIntersecting(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter, playerAttack.position.x, playerAttack.position.y, playerAttack.diameter) == 1)
			{
				enemies[i].lives -= playerAttack.damage;


			}
			
			

			// Deactivate enemy when health is 0
			if (enemies[i].lives == 0) {
				enemies[i].active = 0;
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
			if (bullets[i].position.x - bullets[i].diameter / 2 < 10 || bullets[i].position.x + bullets[i].diameter / 2 > WINDOW_WIDTH - 10 ||
				bullets[i].position.y - bullets[i].diameter / 2 < 10 || bullets[i].position.y + bullets[i].diameter / 2 > WINDOW_HEIGHT - 10) {
				bullets[i].active = 0;
			}
		}
	}

}
