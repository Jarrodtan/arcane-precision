#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include "utils.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#include "itemDrop.h"
#include "obstacle.h"
#include "enemy.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_BULLETS 100  // Maximum bullets in array
#define MAX_ENEMIES 100  // Maximum enemies in array
#define MAX_ITEMS 100

extern float dt;
extern int roomsPassed;
extern struct player player;
extern struct playerAttack playerAttack[MAX_BULLETS];
extern struct itemDrops item[MAX_ITEMS];
extern float obstacle_diameter;
extern int currentObstacleCount;

int difficulty;
int enemyNumber;
CP_Vector bulletMoveD;
CP_Vector bulletMoveN;
CP_Vector enemyMoveD;
CP_Vector enemyMoveN;

//struct enemy enemyStationary[MAX_ENEMIES];
//struct enemy enemyMelee[MAX_ENEMIES];
struct enemy enemies[MAX_ENEMIES];
//struct enemyAttack bullets[MAX_BULLETS]; // Array of bullets

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
	enemyStationary->diameter = 50.0f;
	//enemyStationary->direction = CP_Vector_Set();
	enemyStationary->speed = 0.0f;
	enemyStationary->lives = 1 + difficulty;
	enemyStationary->active = 1;
	enemyStationary->shootTimer = 0.0f;
}
void initialize_enemyMelee(struct enemy* enemyMelee, CP_Vector position) {
	// Initialize enemy properties
	enemyMelee->type = 2;
	enemyMelee->position = position;
	enemyMelee->diameter = 50.0f;
	//enemyMelee->direction = CP_Vector_Set(0,0);
	enemyMelee->speed = 10.0f * difficulty;
	enemyMelee->lives = 2 + difficulty;
	enemyMelee->active = 1;
	
}

void init_enemy(void) 
{
	if (roomsPassed % 5 == 0) 
	{
		difficulty = (roomsPassed / 5) + 1;
	}
	enemyNumber = difficulty;
	// Find an available enemy slot in the array
	//for loop enemyNumber
	//generate rng for enemy position
	for (int i = 0; i < enemyNumber; i++) 
	{
		CP_Vector enemyPosition = CP_Vector_Set(CP_Random_RangeFloat(150.0f, WINDOW_WIDTH - 150.0f), CP_Random_RangeFloat(300.0f, WINDOW_HEIGHT - 300.0f));
		if (enemies[i].active == 0) 
		{
			if(AreCirclesIntersecting(player.position.x, player.position.y, player.diameter, enemyPosition.x, enemyPosition.y, 75.0f) == 1){ 
				CP_Vector enemyPosition = CP_Vector_Set(CP_Random_RangeFloat(150.0f, WINDOW_WIDTH - 150.0f), CP_Random_RangeFloat(300.0f, WINDOW_HEIGHT - 300.0f)); 
			}
			int enemyType = CP_Random_RangeInt(1, 2);
			if (enemyType == 1) 
			{
				//initialise stationary
				initialize_enemyStationary(&enemies[i], enemyPosition);
				enemies[i].bullets->active = 0;
				enemies[i].shootTimer = CP_Random_RangeFloat(0.0f, 2.0f); //give a bit of randomness in each stationary enemies shoot timing so they dont all shoot at the same time.
			}
			else if (enemyType == 2) 
			{
				//initialise melee
				initialize_enemyMelee(&enemies[i], enemyPosition);
			}
		}
	}
}

void enemy_code(void) 
{
	
	// Update and draw all active enemies
	for (int i = 0; i < MAX_ENEMIES; i++) 
	{
		if (enemies[i].active == 1 && enemies[i].type == 1) //stationary enemy
		{ 
				if (enemies[i].isFrozen)
				{
					enemies[i].shootTimer = 0;
					enemies[i].freezeTimer -= dt; // Decrease freeze timer
					if (enemies[i].freezeTimer <= 0)
					{
						enemies[i].isFrozen = 0; // Unfreeze enemy
						enemies[i].speed = (enemies[i].type == 1 ? 10.0f : 0.0f) * difficulty; // Restore speed
					}
				}
				// Draw stationary enemy
				switch (enemies[i].isFrozen)
				{
				case true:
					CP_Settings_Fill(CP_Color_Create(200, 50, 50, 255));
					break;
				case false:
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
					break;
				}
				CP_Graphics_DrawCircle(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter);

				//enemy shooting
				// -----------------------------------------------------------
				// Update shooting timer
				
						enemies[i].shootTimer += (dt * difficulty);

						// Check if 5 seconds have passed to shoot
						if (enemies[i].shootTimer >= 5.0f)
						{
							enemies[i].shootTimer = 0.0f;
							// Calculate bullet direction towards player
							bulletMoveD.x = player.position.x - enemies[i].position.x;
							bulletMoveD.y = player.position.y - enemies[i].position.y;
							bulletMoveN = CP_Vector_Normalize(bulletMoveD);

						// Find an available bullet slot in the array
						for (int j = 0; j < MAX_BULLETS; j++) {
						if (enemies[i].bullets[j].active == 0) 
						{
							// Initialize new bullet
							initialize_bullet(&enemies[i].bullets[j], enemies[i].position, CP_Vector_Scale(bulletMoveN, 1), 400.0f, 1);
							break;
						}
					}
				}

				// Collision and damage logic for when enemy comes in contact with player
				if (CP_Vector_Distance(player.position, enemies[i].position) <= (player.diameter / 2) + (enemies[i].diameter / 2))
				{
					take_damage(&player, 1);
				}
		}	
		else if (enemies[i].active == 1 && enemies[i].type == 2) //melee enemy
		{ 
			if (enemies[i].isFrozen)
			{
				enemies[i].freezeTimer -= dt; // Decrease freeze timer
				if (enemies[i].freezeTimer <= 0)
				{
					enemies[i].isFrozen = 0; // Unfreeze enemy
					enemies[i].speed = (enemies[i].type == 2 ? 10.0f : 0.0f) * difficulty; // Restore speed
				}
			}

			//draw melee enemy
			switch (enemies[i].isFrozen)
			{
			case true:
				CP_Settings_Fill(CP_Color_Create(0, 100, 255, 255));
				break;
			case false:
				CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
				break;
			}
			CP_Graphics_DrawCircle(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter);

			if (!enemies[i].isFrozen)
			{
				// Enemy movement logic for melee enemy
				enemyMoveD.x = player.position.x - enemies[i].position.x;
				enemyMoveD.y = player.position.y - enemies[i].position.y;
				enemyMoveN = CP_Vector_Normalize(enemyMoveD);
				enemies[i].position = CP_Vector_Add(enemies[i].position, CP_Vector_Scale(enemyMoveN, enemies[i].speed * dt));
			}

			// Enemy movement logic for melee enemy (similar to stationary)
			enemyMoveD.x = player.position.x - enemies[i].position.x;
			enemyMoveD.y = player.position.y - enemies[i].position.y;
			enemyMoveN = CP_Vector_Normalize(enemyMoveD);

			enemies[i].direction.x = (enemyMoveN.x * 5) + (rand() % 3 - 1);  // Add randomness to movement
			enemies[i].direction.y = (enemyMoveN.y * 5) + (rand() % 3 - 1);

			// Update melee enemy position
			enemies[i].position = CP_Vector_Add(enemies[i].position, CP_Vector_Scale(enemies[i].direction, enemies[i].speed * dt));

			// Collision and damage logic for when enemy comes in contact with player
			if (CP_Vector_Distance(player.position, enemies[i].position) <= (player.diameter / 2) + (enemies[i].diameter / 2)) 
			{
				take_damage(&player, 1);
			}
		}

		// Update and draw all active bullets
		for (int o = 0; o < MAX_BULLETS; o++) 
		{
			if (enemies[i].bullets[o].active && enemies[i].type == 1) {
				// Move bullet
				enemies[i].bullets[o].position = CP_Vector_Add(enemies[i].bullets[o].position, CP_Vector_Scale(enemies[i].bullets[o].direction, enemies[i].bullets[o].speed * dt));

				// Draw bullet
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Graphics_DrawCircle(enemies[i].bullets[o].position.x, enemies[i].bullets[o].position.y, enemies[i].bullets[o].diameter);

				// Check for collision with player
				if (AreCirclesIntersecting(player.position.x, player.position.y, player.diameter, enemies[i].bullets[o].position.x, enemies[i].bullets[o].position.y, enemies[i].bullets[o].diameter) == 1) {
					take_damage(&player, enemies[i].bullets[o].damage);
					enemies[i].bullets[o].active = 0; // Deactivate bullet upon collision
				}
				// Check for collision with obstacles
				for (int j = 0; j < currentObstacleCount; j++) {
					if (CheckBulletCollision(enemies[i].bullets[o].position, enemies[i].bullets[o].diameter, obstacle[j], obstacle_diameter)) {
						HandleProjectileCollision(&enemies[i].bullets[o]);
						break; // Exit the loop once a collision is detected
					}
				}
				// Deactivate bullet if it goes off-screen
				if (enemies[i].bullets[o].position.x - enemies[i].bullets[o].diameter / 2 < 50 || enemies[i].bullets[o].position.x + enemies[i].bullets[o].diameter / 2 > WINDOW_WIDTH - 50 ||
					enemies[i].bullets[o].position.y - enemies[i].bullets[o].diameter / 2 < 50 || enemies[i].bullets[o].position.y + enemies[i].bullets[o].diameter / 2 > WINDOW_HEIGHT - 50) {
					enemies[i].bullets[o].active = 0;
				}
			}
		}
			for (int p = 0; p < 100; p++)
			{
			//enemy takes dmg when in contact with player attack
			if (AreCirclesIntersecting(enemies[i].position.x, enemies[i].position.y, enemies[i].diameter, playerAttack[p].position.x, playerAttack[p].position.y, playerAttack[p].diameter) == 1
				&& playerAttack[p].isActive == 1 && enemies[i].active == 1)
			{
					playerAttack[p].isActive = 0;

					if (playerAttack[p].selSpell == ICESHARDS)
					{
						enemies[i].isFrozen = 1;
						enemies[i].freezeTimer = 3.0f; // Freeze 3 seconds
						enemies[i].speed = 0; // Stop movement
						enemies[i].lives -= 1;
					}
					else {
						enemies[i].lives -= playerAttack[p].damage;
					}
				// Deactivate enemy when health is 0
					if (enemies[i].lives <= 0) 
					{
						enemies[i].active = 0;
						enemies[i].isFrozen = 0;
						player.score += 10;
						enemyNumber--;

						//initialise item drops
						int r = CP_Random_RangeInt(1, 2); // change here for higher/lower odds of spawning items
						//printf("%d\n", r);//for debugging
						if (r == 1) //RNG for spawning item, 1 in 2 chances
						{
							for (int u = 0; u < MAX_ITEMS; u++)
							{
								if (item[u].active == 0)
								{
									initialize_itemDrop(&item[u], enemies[i].position);
									break;
								}
							}
						}
					}
				}
			}


	}
}

