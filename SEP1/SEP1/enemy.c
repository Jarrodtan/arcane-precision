#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include "utils.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
extern float dt;
extern int roomsPassed;

struct enemy {
	CP_Vector position;
	float diameter;
	float speed;
	CP_Vector direction;
	int lives;
};

struct enemyAttack {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float damage;
	float speed;
	int isFriendly;
	int Spawned;
};

int difficulty = 1;
float bulletdt = 1;
CP_Vector bulletMoveD;
CP_Vector bulletMoveN;
//melee enemy inaccurate homing
CP_Vector enemyMoveD;
CP_Vector enemyMoveN;

struct enemy enemyStationary;
struct enemy enemyMelee;
struct enemyAttack bullet;

	
/*
void enemy_code(CP_Vector player) {
float dt = CP_System_GetDt()
;
	enemyStationary.diameter = 50;
	enemyStationary.position = CP_Vector_Set(WINDOW_WIDTH / 1.5f, WINDOW_HEIGHT / 2.0f);

	enemyMelee.diameter = 50;
	enemyMelee.position = CP_Vector_Set(WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 2.0f);


	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyStationary.position.x, enemyStationary.position.y, enemyStationary.diameter);

	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyMelee.position.x, enemyMelee.position.y, enemyMelee.diameter);
	//-------------------------------------------------------------------------------------------------------------


	if ((int)dt % (1/difficulty) == 0) {
		//shoot_bullet
		bullet.position = enemyStationary.position;
		bullet.isFriendly = 0;
		
		CP_Settings_Fill(CP_Color_Create(242, 103, 75, 255));
		CP_Graphics_DrawCircle(bullet.position.x, bullet.position.y, bullet.diameter);
		bulletdt = CP_System_GetDt() + 5;
	}

	while (bulletdt-1 != 0){
	//add homing to bullet
	bulletMoveD.x = bullet.position.x - player.x;
	bulletMoveD.y = bullet.position.y - player.y;
	}
	

	bulletMoveN = CP_Vector_Normalize(bulletMoveD);
	
	bullet.direction.x = (bulletMoveN.x * difficulty);
	bullet.direction.y = (bulletMoveN.y * difficulty);


	//---------------------------------------------------------------------------------------------------------------



	enemyMoveD.x = enemyMelee.position.x - player.x;
	enemyMoveD.y = enemyMelee.position.y - player.y;

	enemyMoveN = CP_Vector_Normalize(enemyMoveD);
	//add random number to movement
	enemyMelee.direction.x = (enemyMoveN.x * 5) + rand();
	enemyMelee.direction.y = (enemyMoveN.y * 5) + rand();
		
}

//------------------------------------------------------------------------------------------------
*/

void enemy_code(CP_Vector player) {
	static float shootTimer = 0.0f;
	//float dt = CP_System_GetDt();

	// Initialize enemy properties
	enemyStationary.diameter = 50;
	enemyStationary.position = CP_Vector_Set(WINDOW_WIDTH / 1.5f, WINDOW_HEIGHT / 2.0f);

	enemyMelee.diameter = 50;
	//enemyMelee.position = CP_Vector_Set(WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 2.0f);

	// Draw stationary and melee enemies
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(enemyStationary.position.x, enemyStationary.position.y, enemyStationary.diameter);

	// Update shooting timer
	shootTimer += dt;

	// Check if 5 seconds have passed
	if (shootTimer >= 5.0f) {
		shootTimer = 0.0f;  // Reset timer

		// Set bullet initial position, direction, and properties
		bullet.position = enemyStationary.position;
		bullet.isFriendly = 0;
		bullet.diameter = 30;
		bullet.speed = 400.0f;
		bullet.damage = 1;
		bulletdt = 5.0f;  // Initialize bullet timer

		// Calculate bullet direction towards player
		bulletMoveD.x = player.x - bullet.position.x;
		bulletMoveD.y = player.y - bullet.position.y;
		bulletMoveN = CP_Vector_Normalize(bulletMoveD);

		bullet.direction.x = bulletMoveN.x * difficulty;
		bullet.direction.y = bulletMoveN.y * difficulty;
	}
	// Update bullet position over time
	if (bulletdt > 0) {
		bulletdt -= dt;
		//bullet.position.x += bullet.direction.x * dt;
		//bullet.position.y += bullet.direction.y * dt;
		bullet.position = CP_Vector_Add(bullet.position, CP_Vector_Scale(bullet.direction, bullet.speed * dt));

		// Draw bullet
		CP_Settings_Fill(CP_Color_Create(242, 103, 75, 255));
		CP_Graphics_DrawCircle(bullet.position.x, bullet.position.y, bullet.diameter);
	}

	// Enemy movement logic
	enemyMelee.speed = 10.0f;
	enemyMoveD.x = player.x - enemyMelee.position.x;
	enemyMoveD.y = player.y - enemyMelee.position.y;
	enemyMoveN = CP_Vector_Normalize(enemyMoveD);

	enemyMelee.direction.x = (enemyMoveN.x * 5) + (rand() % 3 - 1);  // Add randomness to movement
	enemyMelee.direction.y = (enemyMoveN.y * 5) + (rand() % 3 - 1);
	// Update enemy position with dt for smoother movement
	//enemyMelee.position.x += enemyMelee.direction.x * dt;
//	enemyMelee.position.y += enemyMelee.direction.y * dt;
	enemyMelee.position = CP_Vector_Add(enemyMelee.position, CP_Vector_Scale(enemyMelee.direction, enemyMelee.speed * dt));
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyMelee.position.x, enemyMelee.position.y, enemyMelee.diameter);
}



	

	


