#include "utils.h"
#include "game.h"
#include "mainmenu.h"
#include "enemy.h"
#include "gameover.h"
#include "roomLayout.h"
#include "pause.h"
#include "cprocessing.h"
#include "stdbool.h"
#include <math.h>
#include <stdio.h>
#include "stdlib.h"
#include "obstacle.h"
#include "itemDrop.h"


#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_BULLETS 100  // Maximum bullets in array
#define MAX_ENEMIES 100  // Maximum enemies in array
#define MAX_OBSTACLES 10
#define MAX_ITEMS 100

extern bool isNewGame;
extern bool game_pause;
extern const char* saveFile1;
extern const char* saveFile2;
extern int saveSlot;
extern int difficulty;

CP_Color manaBarColor;
CP_Color manaColor;
CP_Color manaHitboxColor;
CP_Vector player_position;
extern CP_Image pause_sign;
extern CP_Vector obstacle[MAX_OBSTACLES];

//// Obstacle spawn (Bev)
//#define MAX_OBSTACLES (sizeof(obstacle) / sizeof(obstacle[0]))
//CP_Vector obstacle[15]; // obstacle for random spawn
extern int currentObstacleCount;
extern int lastRoom; // Initialize to an invalid room number
extern float obstacle_diameter;

float base_Mana;
float mana;
float random_float;
int cooldown;
int hitboxSpawn;
int roomsPassed; //for increasing difficulty
float dt;
int lastEntered;
bool game_over;

//time manip
float slowTimeScale = 0.1f;
bool isSlowed = false;
enum Spells selectedSpell = FIREBALL;// Default spell



struct player player;
struct manabar maxManabar;
struct manabar currentManabar;
struct manabar manaHitbox;
struct playerAttack playerAttack[100];
struct hearts playerHearts;
extern struct walls topWall;
extern struct walls botWall;
extern struct walls leftWall; 
extern struct walls rightWall;
extern struct enemy enemies[MAX_ENEMIES];
extern struct enemyAttack bullet;
extern struct itemDrops item[MAX_ITEMS];


float slowTime(void) //returns dt value for slowing down time
{
	dt = CP_System_GetDt();
	if (CP_Input_KeyDown(KEY_SPACE))
	{
		isSlowed = true;
		return dt * slowTimeScale;
	}
	else {
	isSlowed = false;
	return dt;
	}
}

void drawSpellMenu(float x, float y, enum Spells selectedSpell) // create spell selection menu. Will require more work
{
	CP_Image fireballIcon = CP_Image_Load("Assets/fireballSpell.png");
	CP_Image iceIcon = CP_Image_Load("Assets/iceshardSpell.png");
	// dim the game to show time is slowed
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 70));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// spell menu dimensions
	float spellSelectWidth = 120.0f;
	float spellSelectHeight = 50.0f;
	float spacing = 20.0f;
	float startX = x - spellSelectWidth - (spacing / 2);
	float startY = y + player.diameter / 2 + 60.0f;

	// highlight which spell is selected
	CP_Color highlightColor = CP_Color_Create(255, 255, 0, 255);
	if (selectedSpell == FIREBALL)
	{
		CP_Settings_Fill(highlightColor);
		CP_Graphics_DrawRect(startX - 5, startY - 5, spellSelectWidth + 10, spellSelectHeight + 10); // create highlight of chosen spell
	}
	else if (selectedSpell == ICESHARDS)
	{
		CP_Settings_Fill(highlightColor);
		CP_Graphics_DrawRect(startX + spellSelectWidth + spacing - 5, startY - 5, spellSelectWidth + 10, spellSelectHeight + 10); // create highlight of chosen spell
	}

	// draw rect 1
	CP_Settings_Fill(CP_Color_Create(255, 100, 100, 255));
	CP_Graphics_DrawRect(startX, startY, spellSelectWidth, spellSelectHeight);

	// draw rect 2
	CP_Settings_Fill(CP_Color_Create(100, 100, 255, 255));
	CP_Graphics_DrawRect(startX + spellSelectWidth + spacing, startY, spellSelectWidth, spellSelectHeight);
	
	// draw fireball icon
	CP_Image_Draw(fireballIcon, startX + (spellSelectWidth / 2), startY + (spellSelectHeight / 2), spellSelectWidth, spellSelectHeight, 255);
	// draw ice icon
	CP_Image_Draw(iceIcon, startX + spellSelectWidth + spacing + (spellSelectWidth / 2), startY + (spellSelectHeight / 2), spellSelectWidth, spellSelectHeight, 255);
	
	fireballIcon = CP_Image_Free;
	iceIcon = CP_Image_Free;
}
void take_damage(struct player* p, int damage) {
	if (p->invincibilityTimer <= 0) {  // Only take damage if not invincible
		if (p->lives > 0) {
			p->lives -= damage;
			if (p->lives <= 0) {
				p->lives = 0;
			}
			// Activate invincibility frames
			p->invincibilityTimer += p->invincibilityDuration;
		}
	}
}
void update_player(float dt) {
	// Decrease the invincibility timer if it's active
	if (player.invincibilityTimer > 0.0f) {
		player.invincibilityTimer -= dt;
		if (player.invincibilityTimer <= 0) {
			player.invincibilityTimer = 0;  // Reset to zero once it expires
		}
	}
}

void saveGame(void)
{
	isNewGame = false;
	playerStats stats = { player.moveSpeed,player.lives,
				player.manaBuildSpeed,player.cooldownSpeed, player.attackDamage,
				player.attackSize, player.attackSpeed,player.score, roomsPassed, lastEntered};
	switch (saveSlot)
	{
	case 1:
		savePlayerStats(&stats, saveFile1);
		break;
	case 2:
		savePlayerStats(&stats, saveFile2);
		break;

	}
}
void initializeAttack(struct playerAttack* playerAttack, CP_Vector position, CP_Vector direction, float speed, int damage, float diameter) {
	playerAttack->position = position;
	playerAttack->direction = direction;
	playerAttack->speed = speed;
	playerAttack->damage = damage;
	playerAttack->diameter = diameter; // Set diameter for each bullet
	playerAttack->isActive = 1;    // Mark bullet as active
}

//===================================================GAME_INIT==================================================================================
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
	random_float = CP_Random_RangeFloat(20, maxManabar.width - manaHitbox.width);
	game_pause = false;
	game_over = false;


	//player
	player.diameter = 60.0f;
	switch (lastEntered)
	{
	case 1:
		player.position = CP_Vector_Set(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 8)*7);
		break;
	case 2:
		player.position = CP_Vector_Set(WINDOW_WIDTH / 8 , WINDOW_HEIGHT / 2);
		break;
	case 3:
		player.position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
		break;
	case 4:
		player.position = CP_Vector_Set((WINDOW_WIDTH / 8)*7, WINDOW_HEIGHT / 2);
		break;
	default:
	player.position = CP_Vector_Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	break;
	}
	player.direction = 1;
	player.active = 1;
	player.invincibilityTimer = 0.0f;
	player.invincibilityDuration = 1.5f;
	if (isNewGame == true) 
	{
	player.moveSpeed = 300.0f;
	player.lives = 3;
	player.manaBuildSpeed = 1.0f;
	player.cooldownSpeed = 1.0f;
	player.attackSize = 30.0f;
	player.attackDamage = 1;
	player.attackSpeed = 500.0f;
	player.score = 0;
	roomsPassed = 0;
	lastEntered = 0;
	}
	else 
	{
		playerStats stats = { player.moveSpeed,player.lives,
	player.manaBuildSpeed,player.cooldownSpeed, player.attackDamage,
	player.attackSize, player.attackSpeed, player.score, roomsPassed, lastEntered};
		switch (saveSlot)
		{
		case 1:
			loadPlayerStats(&stats, saveFile1);
			break;
		case 2:
			loadPlayerStats(&stats, saveFile2);
			break;
		}
		player.moveSpeed = stats.moveSpeed;
		player.lives = stats.lives;
		player.manaBuildSpeed = stats.manaBuildSpeed;
		player.cooldownSpeed = stats.cooldownSpeed;
		player.attackDamage = stats.attackDamage;
		player.attackSize = stats.attackSize;
		player.attackSpeed = stats.attackSpeed;
		player.score = stats.score;
		roomsPassed = stats.roomsPassed;
		lastEntered = stats.lastEntered;
	}

	//max Manabar
	maxManabar.x = player.position.x - player.diameter +2;
	maxManabar.y = player.position.y + 50;
	maxManabar.width = player.diameter*2;
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

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		item[i].active = 0;
	}

	printf("rooms passed: %d\n", roomsPassed);

	//for object spawn
	for (int i = 0; i < currentObstacleCount; i++) {
		InitializeObstacle(i);
	}
	init_enemy();
	roomLayout_init();
}

//===================================================GAME_UPDATE==================================================================================
void Game_Update(void)
{
	dt = slowTime(); // used for slowing downtime

	//GAME OVER trigger
	if (player.lives <= 0) {
		CP_Engine_SetNextGameState(gameover_Init, gameover_Update, gameover_Exit);
		switch (saveSlot)
		{
		case 1:
			remove(saveFile1);
			break;
		case 2:
			remove(saveFile2);
			break;
		}
	}

	UpdateObstacles(roomsPassed, player.position, player.diameter);
	// Check for collisions and handle them
	for (int i = 0; i < currentObstacleCount; i++) {
		if (CheckCollision(player.position, player.diameter, obstacle[i], obstacle_diameter)) {
			HandleCollision(&player.position, player.diameter, obstacle[i], obstacle_diameter);
		}
	}

	// Pause & Resume game
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		switch (game_pause) {
		case true:
			game_pause = false;
			break;
		case false:
			game_pause = true;
			break;
		}
	}

	//debug increment health, score and attack
	if (CP_Input_KeyTriggered(KEY_EQUAL))
	{
		player.lives += 1;
		player.score += 10;
		player.attackDamage += 10;
		printf("score: %d\n", player.score);
	}//debug decrement health, score and attack
	else if (CP_Input_KeyTriggered(KEY_MINUS))
	{
		player.lives -= 1;
		player.score -= 10;
		player.attackDamage += 10;
		printf("score: %d\n", player.score);
	}

	if (game_pause == true) //if game is paused
	{
		for (int i = 0; i < MAX_BULLETS; i++)//drawing of bullets
		{
		if (playerAttack[i].isActive == 1) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
			CP_Graphics_DrawCircle(playerAttack[i].position.x, playerAttack[i].position.y, playerAttack[i].diameter);
		}
		}
		draw_screen();
		pause();
	}

	else if (game_pause == false) {

		//player controls
		if (player.active == 1) {
			if (CP_Input_KeyDown(KEY_W))
			{
				if (player.position.y - (player.diameter / 2)-5 >= topWall.y + topWall.height)
				{
				player.position.y -= player.moveSpeed * dt;
				}
			}
			 if (CP_Input_KeyDown(KEY_S))
			{
				if (player.position.y + (player.diameter / 2)+5 <= botWall.y + botWall.height)
				{
				player.position.y += player.moveSpeed * dt;
				}
			}
			 if (CP_Input_KeyDown(KEY_A))
			{
				if (player.position.x - (player.diameter / 2)-5 >= leftWall.x + leftWall.width)
				{
				player.position.x -= player.moveSpeed * dt;
				}
			}
			 if (CP_Input_KeyDown(KEY_D))
			{
				if (player.position.x + (player.diameter / 2)+5 <= rightWall.x + rightWall.width)
				{
				player.position.x += player.moveSpeed * dt;
				}
			}
		}

		//Attack Mechanic, hold left click to build mana, let go at hitbox to attack.
		if (CP_Input_MouseClicked()) //randomizes hitbox position when mouse clicked in frame
		{
			random_float = CP_Random_RangeFloat(20, maxManabar.width-manaHitbox.width);
		}
		else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) && mana < 100 && cooldown == 0)
		{
			hitboxSpawn = 1;
			mana += player.manaBuildSpeed;
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) && mana >= 0 && cooldown == 0)
		{
			cooldown = 1;
			hitboxSpawn = 0;
			if (manaAreIntersecting(currentManabar.x + (currentManabar.width * (mana / 100)) - 10, 10,
				manaHitbox.x, manaHitbox.width) == 1)
			{
				//spawn player attack flying towards mouse direction till collision with wall
				// Calculate direction from player to mouse
				CP_Vector mousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
				CP_Vector attackDirection = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, player.position));

				// Initialize the player's attack
				for (int i = 0; i < 100; i++)
				{
					if (!playerAttack[i].isActive) {
						// Initialize new bullet
						initializeAttack(&playerAttack[i], player.position, CP_Vector_Scale(attackDirection, 1), player.attackSpeed, player.attackDamage, player.attackSize);
						break;
					}
				}
			}
		}
		if (cooldown == 1 && mana > 0) {
			mana -= player.cooldownSpeed;

		}
		else if (mana <= 0) {
			cooldown = 0;
		}
		for (int i = 0; i < 100; i++)
		{
		if (playerAttack[i].isActive)
		{
			//move attack
			playerAttack[i].position = CP_Vector_Add(playerAttack[i].position, CP_Vector_Scale(playerAttack[i].direction, playerAttack[i].speed * dt));
			
			//draw attack
			if (selectedSpell == FIREBALL)
			{
				CP_Settings_Fill(CP_Color_Create(245, 39, 71, 255)); // Draw Fireball color
				CP_Graphics_DrawCircle(playerAttack[i].position.x, playerAttack[i].position.y, playerAttack[i].diameter);
			}
			else if (selectedSpell == ICESHARDS)
			{
				CP_Settings_Fill(CP_Color_Create(39, 225, 245, 255)); // Draw Ice shard color
				CP_Graphics_DrawCircle(playerAttack[i].position.x, playerAttack[i].position.y, playerAttack[i].diameter);
			}

			//set active to 0 when attack goes off-screen
			if (playerAttack[i].position.x - (playerAttack[i].diameter / 2) < 10 || playerAttack[i].position.x + (playerAttack[i].diameter / 2) > WINDOW_WIDTH - 10 ||
				playerAttack[i].position.y - (playerAttack[i].diameter / 2) < 10 || playerAttack[i].position.y + (playerAttack[i].diameter / 2) > WINDOW_HEIGHT - 10)
			{
				playerAttack[i].isActive = 0;
			}
		}
		}
		draw_screen();
		enemy_code();
		update_player(dt);
		doorInteraction();
		update_item(&item, &player);

		//skill selection
		if (isSlowed)
		{
			if (CP_Input_GetMouseX() >= (player.position.x - 100.0f) - (10.0f) && CP_Input_GetMouseX() <= player.position.x &&
				CP_Input_GetMouseY() >= ((player.position.y + player.diameter / 2) + 60.0f) &&
				CP_Input_GetMouseY() <= ((player.position.y + player.diameter / 2) + 110.0f))
				selectedSpell = FIREBALL;
			else if (CP_Input_GetMouseX() >= player.position.x + 10.0f && CP_Input_GetMouseX() <= player.position.x + 110.0f &&
				CP_Input_GetMouseY() >= ((player.position.y + player.diameter / 2) + 60.0f) &&
				CP_Input_GetMouseY() <= ((player.position.y + player.diameter / 2) + 110.0f))
				selectedSpell = ICESHARDS;
			drawSpellMenu(player.position.x, player.position.y, selectedSpell);
		}
	}
}

void Game_Exit(void)
{
	pause_sign = CP_Image_Free;
	for (int i = 0; i < 100; i++)
	{
	playerAttack[i].isActive = 0;
	}
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].active = 0;
	}

	game_pause = false;
	hitboxSpawn = 0;
	cooldown = 0;
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));

}