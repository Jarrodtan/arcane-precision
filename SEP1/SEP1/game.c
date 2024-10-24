#include "utils.h"
#include "cprocessing.h" //dog
#include "mainmenu.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>
#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define PLAYER_SPEED 400.0f
float territoryDiameter;
float diameter;
CP_Color manaBarColor;
CP_Color manaColor;
CP_Color manaHitboxColor;
CP_Vector player1_position;
float base_Mana;
float mana;
float random_float;
int cooldown;
int hitboxSpawn;
 //wnemy
struct manabar {
	float x;
	float y;
	float width;
	float height;
};

struct player {
	CP_Vector position;
	float diameter;
	int direction;
	int active;
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

struct hearts {
	float x;
	float y;
	float size;
};

struct player player1;
struct manabar maxManabar;
struct manabar currentManabar;
struct manabar manaHitbox;
struct attack playerAttack;
struct attack enemyAttack;
struct hearts playerHearts;

void Game_Init(void)
{
	CP_Settings_RectMode(CP_POSITION_CORNER);
	manaBarColor = CP_Color_Create(0, 0, 150, 255);
	manaColor = CP_Color_Create(0,0,255,255);
	manaHitboxColor = CP_Color_Create(255, 255, 0, 255);
	diameter = 60.0f;
	base_Mana = 100.00f;
	mana = 0.00f;
	cooldown = 0;
	hitboxSpawn = 0;
	random_float = CP_Random_RangeFloat(WINDOW_WIDTH / 2.0f, (WINDOW_WIDTH / 10.0f) * 8.0f);

	//player1
	player1.diameter = diameter;
	player1.position = CP_Vector_Set(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	player1.direction = 1;
	player1.active = 1;
	player1.lives = 7;

	//max Manabar
	maxManabar.x = WINDOW_WIDTH / 10.0f;
	maxManabar.y = WINDOW_HEIGHT / 12.0f;
	maxManabar.width = (WINDOW_WIDTH / 10.0f) * 8.0f;
	maxManabar.height = WINDOW_HEIGHT / 20.0f;

	//current Manabar
	currentManabar.x = WINDOW_WIDTH / 10.0f;
	currentManabar.y = WINDOW_HEIGHT / 12.0f;
	currentManabar.width = (WINDOW_WIDTH / 10.0f)*8.0f;
	currentManabar.height = WINDOW_HEIGHT / 20.0f;

	//Mana HitBox
	manaHitbox.x = (WINDOW_WIDTH / 10.0f)*5.0f;
	manaHitbox.y = WINDOW_HEIGHT / 12.0f;
	manaHitbox.width = (WINDOW_WIDTH / 10.0f);
	manaHitbox.height = WINDOW_HEIGHT / 20.0f;

	playerHearts.x = WINDOW_WIDTH / 2.0f;
	playerHearts.y = WINDOW_HEIGHT / 6.0f;
	playerHearts.size = 15.0f;
}


void Game_Update(void)
{
	// Pause & Resume game
	if (CP_Input_KeyTriggered(KEY_SPACE)) {

	}

	float dt = CP_System_GetDt();
	//player 1 controls
	if (player1.active == 1) {
		if (CP_Input_KeyDown(KEY_W))
		{
			player1.position.y -= PLAYER_SPEED * dt;
		}
		else if (CP_Input_KeyDown(KEY_S))
		{
			player1.position.y += PLAYER_SPEED * dt;
		}
		else if (CP_Input_KeyDown(KEY_A))
		{
			player1.position.x -= PLAYER_SPEED * dt;
		}
		else if (CP_Input_KeyDown(KEY_D))
		{
			player1.position.x += PLAYER_SPEED * dt;
		}
	}
	//re-sets mana hitbox position for randomness
	manaHitbox.x = random_float;
	
	//Attack Mechanic, hold left click to build mana, let go at hitbox to attack.
	if (CP_Input_MouseClicked()) //randomizes hitbox position when mouse clicked in frame
	{
		random_float = CP_Random_RangeFloat(WINDOW_WIDTH/ 1.3f, (WINDOW_WIDTH / 10.0f));
	}
	 else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) && mana < 100 && cooldown == 0)
	{
		hitboxSpawn = 1;
		mana += 1.0f;
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && mana >= 0) 
	{
		cooldown = 1;
		hitboxSpawn = 0;
		if (AreIntersecting((currentManabar.width * (mana / 100.0f)),
			manaHitbox.x, manaHitbox.width) && mana > 0.0f)
		{
			//spawn player attack flying towards mouse direction till collision with wall
			// Calculate direction from player to mouse
			CP_Vector mousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
			CP_Vector attackDirection = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, player1.position));

			// Initialize the player's attack
			playerAttack.position = player1.position;
			playerAttack.speed = 500.0f; // speed of the attack
			playerAttack.isFriendly = 1; // indicate that it's a player attack
			playerAttack.Spawned = 1;
			playerAttack.diameter = 30.0f;
			playerAttack.direction = attackDirection;

			printf("Attack Spawned! Heading towards mouse direction.\n");
		}
	}
	if (cooldown == 1 && mana > 0) {
		mana -= 1.0f;
	
	}
	else if (mana == 0) {
		cooldown = 0;
	}


	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));

	//draw player 1
	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(player1.position.x, player1.position.y, diameter);

	if (playerAttack.Spawned == 1)
	{
		playerAttack.position = CP_Vector_Add(playerAttack.position, CP_Vector_Scale(playerAttack.direction, playerAttack.speed * dt));
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255)); // Yellow for attack
		CP_Graphics_DrawCircle(playerAttack.position.x, playerAttack.position.y, playerAttack.diameter);

		if (playerAttack.position.x < 0 || playerAttack.position.x > WINDOW_WIDTH ||
			playerAttack.position.y < 0 || playerAttack.position.y > WINDOW_HEIGHT)
		{
			playerAttack.Spawned = 0; // deactivate the attack
			printf("Attack destroyed after hitting the wall.\n");
		}
	}

	//ManaBar
	CP_Settings_Fill(manaBarColor);
	CP_Graphics_DrawRect(maxManabar.x,maxManabar.y,maxManabar.width,maxManabar.height);

	//Current Mana
	if (cooldown == 0) {
	CP_Settings_Fill(manaColor);
	CP_Graphics_DrawRect(currentManabar.x, currentManabar.y, (currentManabar.width)*(mana/100), currentManabar.height);
	}
	else {
		CP_Settings_Fill(CP_Color_Create(255,0,0,255));
		if (CP_Input_MouseClicked()) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		}
		CP_Graphics_DrawRect(currentManabar.x, currentManabar.y, (currentManabar.width*(mana / 100)), currentManabar.height);
	}

	//Mana Hitbox
	if (hitboxSpawn == 1) {
	CP_Settings_Fill(manaHitboxColor);
	CP_Graphics_DrawRect(manaHitbox.x, manaHitbox.y, manaHitbox.width, manaHitbox.height);
	}

	//Mana cursor
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(currentManabar.x+(currentManabar.width*(mana/100))-10, currentManabar.y, 10, currentManabar.height);

	//hearts
	//additional hearts
	switch (player1.lives) 
	{
	case 4: 
		drawHearts(playerHearts.x, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 100, playerHearts.y, playerHearts.size);
		break;
	case 5: 
		drawHearts(playerHearts.x, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 100, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 100, playerHearts.y, playerHearts.size);
		break;
	case 6:
		drawHearts(playerHearts.x, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 100, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 100, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 150, playerHearts.y, playerHearts.size);
		break;
	case 7:
		drawHearts(playerHearts.x, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 100, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 100, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 150, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 150, playerHearts.y, playerHearts.size);
		break;
	default:
		drawHearts(playerHearts.x, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x - 50, playerHearts.y, playerHearts.size);
		drawHearts(playerHearts.x + 50, playerHearts.y, playerHearts.size);
	}

	//return to mainmenu
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

}

void Game_Exit(void)
{

}