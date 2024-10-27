#include "utils.h"
#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include "stdbool.h"
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define PLAYER_SPEED 400.0f

CP_Color manaBarColor;
CP_Color manaColor;
CP_Color manaHitboxColor;
CP_Vector player1_position;
CP_Image pause_sign;

float territoryDiameter;
float diameter;
float base_Mana;
float mana;
float random_float;
int cooldown;
int hitboxSpawn;

bool game_pause;

//enemy
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
	int maxLives;
	int currentLives;
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
	float spacing;
};

struct player player1;
struct manabar maxManabar;
struct manabar currentManabar;
struct manabar manaHitbox;
struct attack playerAttack;
struct attack enemyAttack;
struct hearts playerHearts;

void static draw_screen(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));

	//draw player 1
	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(player1.position.x, player1.position.y, player1.diameter);

	//ManaBar
	maxManabar.x = player1.position.x - player1.diameter +2;
	maxManabar.y = player1.position.y + 50;
	CP_Settings_Fill(manaBarColor);
	CP_Graphics_DrawRect(maxManabar.x, maxManabar.y, maxManabar.width, maxManabar.height);

	//Current Mana
	currentManabar.x = maxManabar.x;
	currentManabar.y = maxManabar.y;
	if (cooldown == 0) {
		CP_Settings_Fill(manaColor);
		CP_Graphics_DrawRect(currentManabar.x, currentManabar.y, (currentManabar.width) * (mana / 100), currentManabar.height);
	}
	else {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		if (CP_Input_MouseClicked()) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		}
		CP_Graphics_DrawRect(currentManabar.x, currentManabar.y, (currentManabar.width * (mana / 100)), currentManabar.height);
	}

	//Mana Hitbox
	manaHitbox.y = maxManabar.y;
	if (hitboxSpawn == 1) {
		CP_Settings_Fill(manaHitboxColor);
		CP_Graphics_DrawRect(manaHitbox.x, manaHitbox.y, manaHitbox.width, manaHitbox.height);
	}

	//Mana cursor
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(currentManabar.x + (currentManabar.width * (mana / 100)) - 5, currentManabar.y, 5, currentManabar.height);


	// Max hearts per row
	int heartsPerRow = 5;
	for (int i = 0; i < player1.maxLives; i++) {
		int row = i / heartsPerRow;
		int col = i % heartsPerRow;

		// Calculate the x and y positions for the heart based on row and column
		float xPosition = playerHearts.x + col * playerHearts.spacing;
		float yPosition = playerHearts.y + row * playerHearts.size * 2.5f;// adjusts spacing between rows

		// Draw the heart at the calculated position
		drawHearts(xPosition, yPosition, playerHearts.size);
	}

}

void Game_Init(void)
{
	pause_sign = CP_Image_Load("Assets/Pause Sign.png");
	CP_Settings_RectMode(CP_POSITION_CORNER);
	manaBarColor = CP_Color_Create(0, 0, 150, 255);
	manaColor = CP_Color_Create(0, 0, 255, 255);
	manaHitboxColor = CP_Color_Create(255, 255, 0, 255);
	base_Mana = 100.00f;
	mana = 0.00f;
	cooldown = 0;
	hitboxSpawn = 0;
	random_float = CP_Random_RangeFloat(0, maxManabar.width - manaHitbox.width);
	game_pause = false;
	playerAttack.Spawned = 0;

	//player1
	player1.diameter = 60.0f;
	player1.position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	player1.direction = 1;
	player1.active = 1;
	player1.maxLives = 3;
	player1.currentLives = player1.maxLives;

	//max Manabar
	maxManabar.x = player1.position.x - diameter +2;
	maxManabar.y = player1.position.y + 50;
	maxManabar.width = player1.diameter*2;
	maxManabar.height = 20;

	//current Manabar
	currentManabar.x = maxManabar.x;
	currentManabar.y = maxManabar.y;
	currentManabar.width = maxManabar.width;
	currentManabar.height = maxManabar.height;

	//Mana HitBox
	manaHitbox.x = maxManabar.x;
	manaHitbox.y = maxManabar.y;
	manaHitbox.width = 20;
	manaHitbox.height = maxManabar.height;

	//player hearts
	playerHearts.x = WINDOW_WIDTH / 30.0f;
	playerHearts.y = WINDOW_HEIGHT / 24.0f;
	playerHearts.size = 15.0f;
	playerHearts.spacing = 50;
}


void Game_Update(void)
{
	float dt = CP_System_GetDt();

	// Pause & Resume game
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		switch (game_pause) {
		case true:
			game_pause = false;
			break;
		case false:
			game_pause = true;
			break;
		}
	}

	//return to mainmenu (To be removed)
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	//testing lives
	if (CP_Input_KeyTriggered(KEY_N))
	{
		player1.maxLives += 1;
	}
	else if (CP_Input_KeyTriggered(KEY_M))
	{
		player1.maxLives -= 1;
	}

	if (game_pause == true) {
		if (playerAttack.Spawned == 1) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
			CP_Graphics_DrawCircle(playerAttack.position.x, playerAttack.position.y, playerAttack.diameter);
		}
		draw_screen();

		//dim background and show pause sign
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
		CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		CP_Image_Draw(pause_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 300.0f, 300.0f, 255);
		CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
	}

	else if (game_pause == false) {
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
		manaHitbox.x = maxManabar.x + random_float;

		//Attack Mechanic, hold left click to build mana, let go at hitbox to attack.
		if (CP_Input_MouseClicked()) //randomizes hitbox position when mouse clicked in frame
		{
			random_float = CP_Random_RangeFloat(0, maxManabar.width-manaHitbox.width);
		}
		else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) && mana < 100 && cooldown == 0)
		{
			hitboxSpawn = 1;
			mana += 1.0f;
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && mana >= 0 && cooldown == 0)
		{
			cooldown = 1;
			hitboxSpawn = 0;
			if (AreIntersecting(currentManabar.x + (currentManabar.width * (mana / 100)) - 10, 10,
				manaHitbox.x, manaHitbox.width) == 1)
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
			}
		}
		if (cooldown == 1 && mana > 0) {
			mana -= 1.0f;

		}
		else if (mana == 0) {
			cooldown = 0;
		}

		if (playerAttack.Spawned == 1)
		{
			playerAttack.position = CP_Vector_Add(playerAttack.position, CP_Vector_Scale(playerAttack.direction, playerAttack.speed * dt));
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255)); // Yellow for attack
			CP_Graphics_DrawCircle(playerAttack.position.x, playerAttack.position.y, playerAttack.diameter);

			if (playerAttack.position.x < 0 || playerAttack.position.x > WINDOW_WIDTH ||
				playerAttack.position.y < 0 || playerAttack.position.y > WINDOW_HEIGHT)
			{
				playerAttack.Spawned = 0;
			}
		}
		draw_screen();

	}
}

void Game_Exit(void)
{
	playerAttack.Spawned = 0;
	game_pause = false;
	hitboxSpawn = 0;
	cooldown = 0;
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));

}