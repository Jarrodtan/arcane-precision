#include "utils.h"
#include "game.h"
#include "cprocessing.h"
#include "mainmenu.h"
#include "enemy.h"
#include "gameover.h"
#include "stdbool.h"
#include <math.h>
#include <stdio.h>
#include "stdlib.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
extern int saveSlot;
extern bool isNewGame;
extern const char* saveFile1;
extern const char* saveFile2;
float dt;
int lastEntered;

CP_Color manaBarColor;
CP_Color manaColor;
CP_Color manaHitboxColor;
CP_Vector player_position;
CP_Image pause_sign;

float territoryDiameter;
float diameter;
float base_Mana;
float mana;
float random_float;
int cooldown;
int hitboxSpawn;
int roomsPassed; //for increasing difficulty
extern int difficulty;

//time manip
float slowTimeScale = 0.1f;
bool isSlowed = false;
int selectedSpell = 0;

bool game_pause, game_over;

struct manabar {
	float x;
	float y;
	float width;
	float height;
};

struct playerAttack {
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

struct walls {
	float x;
	float y;
	float width;
	float height;
};

struct player player;
struct manabar maxManabar;
struct manabar currentManabar;
struct manabar manaHitbox;
struct playerAttack playerAttack;
struct hearts playerHearts;
struct walls topWall;
struct walls botWall;
struct walls leftWall; 
struct walls rightWall;
struct walls topDoor;
struct walls botDoor;
struct walls leftDoor;
struct walls rightDoor;
extern struct enemy enemyStationary;
extern struct enemy enemyMelee;
extern struct enemyAttack bullet;

void static draw_screen(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));

	//Walls for room
	CP_Settings_Fill(CP_Color_Create(100, 30, 50, 255));
	CP_Graphics_DrawRect(topWall.x,topWall.y,topWall.width,topWall.height);
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

	//draw player 1
	if (player.invincibilityTimer > 0) 
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
	maxManabar.x = player.position.x - player.diameter +2;
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

}

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

void drawSpellMenu(float x, float y) //create spell selection menu. Will require more work
{
	//dim the game to show time is slowed
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 70));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//spell menu dimensions
	float spellSelectWidth = 100.0f;
	float spellSelectHeight = 50.0f;
	float spacing = 20.0f;
	float startX = x - spellSelectWidth - (spacing / 2);
	float startY = y + player.diameter / 2 + 60.0f;

	//highlight which spell is selected
	CP_Color highlightColor = CP_Color_Create(255, 255, 0, 255);
	if (selectedSpell == 0)
	{
		CP_Settings_Fill(highlightColor);
		CP_Graphics_DrawRect(startX - 5, startY - 5, spellSelectWidth + 10, spellSelectHeight + 10); //create highlight of chosen spell
	}
	else if (selectedSpell == 1)
	{
		CP_Settings_Fill(highlightColor);
		CP_Graphics_DrawRect(startX + spellSelectWidth + spacing - 5, startY - 5, spellSelectWidth + 10, spellSelectHeight + 10); //create highlight of chosen spell
	}


	//draw rect 1
	CP_Settings_Fill(CP_Color_Create(255, 100, 100, 255));
	CP_Graphics_DrawRect(startX, startY, spellSelectWidth, spellSelectHeight);

	//draw rect 2
	CP_Settings_Fill(CP_Color_Create(100, 100, 255, 255));
	CP_Graphics_DrawRect(startX + spellSelectWidth + spacing, startY, spellSelectWidth, spellSelectHeight);

	//text (needs work)
	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	float textX1 = startX + spellSelectWidth / 2 - 15; //need to change
	float textY1 = startY + spellSelectHeight / 2 - 8; //not aligned
	CP_Font_DrawText("Fireball", textX1, textY1);

	float textX2 = startX + spellSelectWidth + spacing + spellSelectWidth / 2 - 10;//need to change
	float textY2 = startY + spellSelectHeight / 2 - 8;//not aligned
	CP_Font_DrawText("Ice", textX2, textY2);

}
void take_damage(struct player* p, int damage) {
	if (p->invincibilityTimer <= 0) {  // Only take damage if not invincible
		if (p->lives > 0) {
			p->lives -= damage;
			if (p->lives <= 0) {
				p->lives = 0;
				printf("Player defeated!\n");
			}
			else {
				printf("Player damaged! Lives remaining: %d\n", p->lives);
			}
			// Activate invincibility frames
			p->invincibilityTimer += p->invincibilityDuration;
			printf("%f", p->invincibilityDuration);
			printf("%f",p->invincibilityTimer);
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
	playerAttack.Spawned = 0;

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
	player.moveSpeed = 400.0f;
	player.lives = 3;
	player.manaBuildSpeed = 1.0f;
	player.cooldownSpeed = 1.0f;
	player.attackSize = 30.0f;
	player.attackDamage = 1;
	player.attackSpeed = 500.0f;
	player.score = 0;
	roomsPassed = 0;
	}
	else 
	{
		playerStats stats = { player.moveSpeed,player.lives,
	player.manaBuildSpeed,player.cooldownSpeed, player.attackDamage,
	player.attackSize, player.attackSpeed, player.score, roomsPassed};
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
	}

	//max Manabar
	maxManabar.x = player.position.x - diameter +2;
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

	//walls
	topWall.x = 0;
	topWall.y = 0;
	topWall.width = WINDOW_WIDTH;
	topWall.height = 10;

	rightWall.x = WINDOW_WIDTH;
	rightWall.y = 0;
	rightWall.width = -10;
	rightWall.height = WINDOW_HEIGHT;

	botWall.x = WINDOW_WIDTH;
	botWall.y = WINDOW_HEIGHT;
	botWall.width = -WINDOW_WIDTH;
	botWall.height = -10;

	leftWall.x = 0;
	leftWall.y = WINDOW_HEIGHT;
	leftWall.width = 10;
	leftWall.height = -WINDOW_HEIGHT;

	//doors
	topDoor.x = (WINDOW_WIDTH / 2) - 100;
	topDoor.y = 0;
	topDoor.width = 200;
	topDoor.height = 10;

	rightDoor.x = WINDOW_WIDTH-10;
	rightDoor.y = (WINDOW_HEIGHT / 2) - 100;
	rightDoor.width = 10;
	rightDoor.height = 200;

	botDoor.x = (WINDOW_WIDTH / 2) - 100;
	botDoor.y = WINDOW_HEIGHT-10;
	botDoor.width = 200;
	botDoor.height = 10;

	leftDoor.x = 0;
	leftDoor.y = (WINDOW_HEIGHT / 2) - 100;
	leftDoor.width = 10;
	leftDoor.height = 200;

	printf("rooms passed: %d\n", roomsPassed);
	printf("score: %d\n", player.score);
	printf("isNewGame? %d \n", isNewGame);
}

void saveGame(void)
{
	isNewGame = false;
	playerStats stats = { player.moveSpeed,player.lives,
				player.manaBuildSpeed,player.cooldownSpeed, player.attackDamage,
				player.attackSize, player.attackSpeed,player.score, roomsPassed };
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

//intereactions with doors
void doorInteraction(void)
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


void Game_Update(void)
{
	// Testing Gameover sign
	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		CP_Engine_SetNextGameState(gameover_Init, gameover_Update, gameover_Exit);
	}

	dt = slowTime();
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
	//testing lives
	if (CP_Input_KeyTriggered(KEY_EQUAL))
	{
		player.lives += 1;
		player.attackSize += 10;
		player.score += 10;
	}
	else if (CP_Input_KeyTriggered(KEY_MINUS))
	{
		player.lives -= 1;
		player.attackSize -= 10;
		player.score -= 10;
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

		CP_Settings_Fill(CP_Color_Create(240, 230, 140, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, WINDOW_HEIGHT / 2.4f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Main Menu", WINDOW_WIDTH / 2.3f, WINDOW_HEIGHT / 2.11f);
		CP_Image_Draw(pause_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f, 100.0f, 100.0f, 255);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Press escape key to continue!", WINDOW_WIDTH / 3.0f, WINDOW_HEIGHT / 1.4f);

		CP_Settings_TextSize(30.0f);
		CP_Font_DrawText("Movement controls: W - Up | S - Down | A - Left | D - Right", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.8f);
		CP_Font_DrawText("Attack controls: Mouse left click - Charge Mana", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.7f);
		CP_Font_DrawText("Special ability: Space - Spell Selection", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.61f);
		CP_Font_DrawText("Pause / Resume: Esc Key", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.53f);

		//return to mainmenu
		if (IsAreaClicked(WINDOW_WIDTH / 1.99f, WINDOW_HEIGHT / 2.2f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
		CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
	}

	else if (game_pause == false) {
		//player 1 controls
		if (player.active == 1) {
			if (CP_Input_KeyDown(KEY_W))
			{
				if (player.position.y - (player.diameter / 2)-5 >= topWall.y + topWall.height)
				{
				player.position.y -= player.moveSpeed * dt;
				}
			}
			else if (CP_Input_KeyDown(KEY_S))
			{
				if (player.position.y + (player.diameter / 2)+5 <= botWall.y + botWall.height)
				{
				player.position.y += player.moveSpeed * dt;
				}
			}
			else if (CP_Input_KeyDown(KEY_A))
			{
				if (player.position.x - (player.diameter / 2)-5 >= leftWall.x + leftWall.width)
				{
				player.position.x -= player.moveSpeed * dt;
				}
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				if (player.position.x + (player.diameter / 2)+5 <= rightWall.x + rightWall.width)
				{
				player.position.x += player.moveSpeed * dt;
				}
			}
		}
		//skill selection
		if (isSlowed)
		{
			if (CP_Input_KeyDown(KEY_A)) selectedSpell = 0; //default (fireball)
			else if (CP_Input_KeyDown(KEY_D)) selectedSpell = 1; //ice 
			drawSpellMenu(player.position.x, player.position.y);
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
				playerAttack.position = player.position;
				playerAttack.speed = player.attackSpeed; // speed of the attack
				playerAttack.isFriendly = 1; // indicate that it's a player attack
				playerAttack.Spawned = 1;
				playerAttack.diameter = player.attackSize;
				playerAttack.direction = attackDirection;
			}
		}
		if (cooldown == 1 && mana > 0) {
			mana -= player.cooldownSpeed;

		}
		else if (mana <= 0) {
			cooldown = 0;
		}

		if (playerAttack.Spawned == 1)
		{
			playerAttack.position = CP_Vector_Add(playerAttack.position, CP_Vector_Scale(playerAttack.direction, playerAttack.speed * dt));
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255)); // Yellow for attack
			CP_Graphics_DrawCircle(playerAttack.position.x, playerAttack.position.y, playerAttack.diameter);

			if (playerAttack.position.x - (playerAttack.diameter/2) < 10 || playerAttack.position.x + (playerAttack.diameter / 2) > WINDOW_WIDTH-10 ||
				playerAttack.position.y - (playerAttack.diameter / 2) < 10 || playerAttack.position.y + (playerAttack.diameter / 2) > WINDOW_HEIGHT-10)
			{
				playerAttack.Spawned = 0;
			}
		}
		draw_screen();
		enemy_code(player);
		update_player(dt);
		doorInteraction();
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