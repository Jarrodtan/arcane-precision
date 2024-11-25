#pragma once
#include "cprocessing.h"
#include "game.h"
#include "roomLayout.h"
#include "utils.h"
#include "enemy.h"
#include "stdio.h"
#include "string.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f


struct walls topWall = { 0,0,WINDOW_WIDTH,50 };
struct walls rightWall = { WINDOW_WIDTH, 0, -50, WINDOW_HEIGHT };
struct walls botWall = { WINDOW_WIDTH, WINDOW_HEIGHT, -WINDOW_WIDTH, -50 };
struct walls leftWall = { 0, WINDOW_HEIGHT, 50, -WINDOW_HEIGHT };

struct walls topDoor = { (WINDOW_WIDTH / 2) - 100, 0, 200, 50 };
struct walls rightDoor = { WINDOW_WIDTH - 50, (WINDOW_HEIGHT / 2) - 100 , 50, 200 };
struct walls botDoor = { (WINDOW_WIDTH / 2) - 100, WINDOW_HEIGHT - 50, 200, 50 };
struct walls leftDoor = { 0,(WINDOW_HEIGHT / 2) - 100, 50, 200 };

extern struct player player;
extern struct manabar maxManabar;
extern struct manabar currentManabar;
extern struct manabar manaHitbox;
extern struct hearts playerHearts;

extern CP_Color manaBarColor;
extern CP_Color manaColor;
extern CP_Color manaHitboxColor;

extern int lastEntered;
extern int roomsPassed;
extern int cooldown;
extern float base_Mana;
extern float mana;
extern float random_float;
extern int hitboxSpawn;
extern int enemyNumber;
extern CP_Font myFont;
char roomsDisplay[256];
char scoreDisplay[256];
float textSize;
extern enum Spells selectedSpell;


void draw_Room()
{
	//Walls for room
	CP_Settings_Fill(CP_Color_Create(100, 30, 50, 255));
	CP_Graphics_DrawRect(topWall.x, topWall.y, topWall.width, topWall.height);
	CP_Graphics_DrawRect(botWall.x, botWall.y, botWall.width, botWall.height);
	CP_Graphics_DrawRect(leftWall.x, leftWall.y, leftWall.width, leftWall.height);
	CP_Graphics_DrawRect(rightWall.x, rightWall.y, rightWall.width, rightWall.height);

	//Doors for rooms
	switch (lastEntered)
	{
	case 1: //blocks bottom door when player entered top door
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(botDoor.x, botDoor.y, botDoor.width, botDoor.height);
		CP_Settings_Fill(CP_Color_Create(255, 255, 200, 255));
		CP_Graphics_DrawRect(topDoor.x, topDoor.y, topDoor.width, topDoor.height);
		CP_Graphics_DrawRect(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height);
		CP_Graphics_DrawRect(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height);
		break;
	case 2: //blocks left door when player entered right door
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height);
		CP_Settings_Fill(CP_Color_Create(255, 255, 200, 255));
		CP_Graphics_DrawRect(topDoor.x, topDoor.y, topDoor.width, topDoor.height);
		CP_Graphics_DrawRect(botDoor.x, botDoor.y, botDoor.width, botDoor.height);
		CP_Graphics_DrawRect(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height);
		break;
	case 3:  //blocks top door when player entered bottom door
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(topDoor.x, topDoor.y, topDoor.width, topDoor.height);
		CP_Settings_Fill(CP_Color_Create(255, 255, 200, 255));
		CP_Graphics_DrawRect(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height);
		CP_Graphics_DrawRect(botDoor.x, botDoor.y, botDoor.width, botDoor.height);
		CP_Graphics_DrawRect(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height);
		break;
	case 4:  //blocks right door when player entered left door
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height);
		CP_Settings_Fill(CP_Color_Create(255, 255, 200, 255));
		CP_Graphics_DrawRect(topDoor.x, topDoor.y, topDoor.width, topDoor.height);
		CP_Graphics_DrawRect(botDoor.x, botDoor.y, botDoor.width, botDoor.height);
		CP_Graphics_DrawRect(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height);
		break;
	default: //dont block any doors
		CP_Settings_Fill(CP_Color_Create(255, 255, 200, 255));
		CP_Graphics_DrawRect(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height);
		CP_Graphics_DrawRect(topDoor.x, topDoor.y, topDoor.width, topDoor.height);
		CP_Graphics_DrawRect(botDoor.x, botDoor.y, botDoor.width, botDoor.height);
		CP_Graphics_DrawRect(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height);
		break;
	}
}

//interactions with doors
void doorInteraction(void)
{
	if (enemyNumber <= 0) 
	{
	if (doorIntersect(player.position.x, player.position.y, player.diameter, topDoor.x, topDoor.y, topDoor.width, topDoor.height) == 1 && lastEntered != 3)
	{
		//set last entered and next spawn point
		lastEntered = 1;
		roomsPassed++;
		saveGame();
		Game_Init();
	}
	if (doorIntersect(player.position.x, player.position.y, player.diameter, rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height) == 1 && lastEntered != 4)
	{
		lastEntered = 2;
		roomsPassed++;
		saveGame();
		Game_Init();
	}
	if (doorIntersect(player.position.x, player.position.y, player.diameter, botDoor.x, botDoor.y, botDoor.width, botDoor.height) == 1 && lastEntered != 1)
	{
		lastEntered = 3;
		roomsPassed++;
		saveGame();
		Game_Init();
	}
	if (doorIntersect(player.position.x, player.position.y, player.diameter, leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height) == 1 && lastEntered != 2)
	{
		lastEntered = 4;
		roomsPassed++;
		saveGame();
		Game_Init();
	}
	}
}

void roomLayout_init(void)
{
	sprintf_s(roomsDisplay, sizeof(roomsDisplay), "Room Passed: %d", roomsPassed);
	sprintf_s(scoreDisplay, sizeof(scoreDisplay), "Score: %d", player.score);
	textSize = 30.0f;
	CP_Settings_TextSize(textSize);
}

void draw_screen(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
	draw_Room();

	//draw player 1

	// darw outline for spells
	switch (selectedSpell)
	{
	case (FIREBALL):
		CP_Settings_Fill(CP_Color_Create(240, 150, 0, 255)); // Draw Fire outline
		break;
	case (ICESHARDS):
		CP_Settings_Fill(CP_Color_Create(39, 225, 245, 255)); // Draw Ice outline
		break;
	}
		CP_Graphics_DrawCircle(player.position.x, player.position.y, player.diameter + 10.0f);
	if (player.invincibilityTimer > 0) // Flash black and original color to signify Invincibility frame
	{
		if ((int)(player.invincibilityTimer * 10) % 2 == 0) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));  // Black color
		}
		else {
			CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));  // Original color
		}
	}
	else {
		// Normal color when not invincible
		CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	}
	CP_Graphics_DrawCircle(player.position.x, player.position.y, player.diameter);


	//ManaBar
	maxManabar.x = player.position.x - player.diameter + 2;
	maxManabar.y = player.position.y + 50;
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
	//re-sets mana hitbox position for randomness
	manaHitbox.x = maxManabar.x + random_float;
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
	for (int i = 0; i < player.lives; i++) {
		int row = i / heartsPerRow;
		int col = i % heartsPerRow;

		// Calculate the x and y positions for the heart based on row and column
		float xPosition = playerHearts.x + col * playerHearts.spacing;
		float yPosition = playerHearts.y + row * playerHearts.size * 2.5f;// adjusts spacing between rows

		// Draw the heart at the calculated position
		drawHearts(xPosition, yPosition, playerHearts.size);
	}
	//display score and rooms passsed
	CP_Font_Set(myFont);
	textSize = 30.0f;
	CP_Settings_TextSize(textSize);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	sprintf_s(roomsDisplay, sizeof(roomsDisplay), "Room Passed: %d", roomsPassed);
	sprintf_s(scoreDisplay, sizeof(scoreDisplay), "Score: %d", player.score);
	CP_Font_DrawText(roomsDisplay, WINDOW_WIDTH - 250, 85);
	CP_Font_DrawText(scoreDisplay, WINDOW_WIDTH - 250, 115);
}
