#include "utils.h"
#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>
#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

struct player {
	CP_Vector position;
	float diameter;
	int direction;
	int active;
	int lives;
};

struct enemy {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	int lives;
	
};


struct attack {
	CP_Vector position;
	float diameter;
	CP_Vector direction;
	float damage;
	float speed;
	int isFriendly;
	int Spawned;
};

int difficulty = 1;

struct player player1;
struct enemy enemyStationary;
struct enemy enemyMelee;
struct attack bullet;



	

void enemy_code(void) {
	enemyStationary.diameter = 5;
	enemyStationary.position = CP_Vector_Set(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 2);

	enemyMelee.diameter = 5;
	enemyMelee.position = CP_Vector_Set(WINDOW_WIDTH / 2.5, WINDOW_HEIGHT / 2);


	//player1.position = CP_Vector_Set(1, 1);



	

	float dt = CP_System_GetDt();
	float bulletdt;

	



	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyStationary.position.x, enemyStationary.position.y, enemyStationary.diameter);

	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(enemyMelee.position.x, enemyMelee.position.y, enemyMelee.diameter);
	//-------------------------------------------------------------------------------------------------------------


	if ((int)dt % (1/difficulty) == 0) {
		//shoot_bullet //lol
		bullet.position = enemyStationary.position;
		bullet.isFriendly = 0;
		

		CP_Settings_Fill(CP_Color_Create(242, 103, 75, 255));
		CP_Graphics_DrawCircle(bullet.position.x, bullet.position.y, bullet.diameter);
		bulletdt = CP_System_GetDt() + 5;
	}


	CP_Vector bulletMoveD;
	CP_Vector bulletMoveN;



	while (dt - bulletdt != 0){
		//add homing to bullet
	bulletMoveD.x = bullet.position.x - player1.position.x;
	bulletMoveD.y = bullet.position.y - player1.position.y;
	}

	bulletMoveN = CP_Vector_Normalize(bulletMoveD);
	
	bullet.direction.x = (bulletMoveN.x * difficulty);
	bullet.direction.y = (bulletMoveN.y * difficulty);





	//---------------------------------------------------------------------------------------------------------------



	//melee enemy inaccurate homing
	CP_Vector enemyMoveD;
	CP_Vector enemyMoveN;



	enemyMoveD.x = enemyMelee.position.x - player1.position.x;
	enemyMoveD.y = enemyMelee.position.y - player1.position.y;

	enemyMoveN = CP_Vector_Normalize(enemyMoveD);
	//add random number to movement
	enemyMelee.direction.x = (enemyMoveN.x * 5) + rand();
	enemyMelee.direction.y = (enemyMoveN.y * 5) + rand();

}

//------------------------------------------------------------------------------------------------

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2) {
	//check if player touches enemy

	if ((c1_x - c2_x) * (c1_x - c2_x) + (c1_y - c2_y) * (c1_y - c2_y) <= (r1 + r2) * (r1 + r2)) {
		return 1;
	}
	else {
		return 0;
	}


}
	

	


