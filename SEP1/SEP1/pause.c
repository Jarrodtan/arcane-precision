#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include "utils.h"
#include "pause.h"
#include "stdbool.h"
#include "startmenu.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

CP_Image pause_sign;
bool game_pause;
bool how_To;
extern CP_Font myFont;
float textSize;
int page;
float item_x;
float item_y;


void pause(void) 
{

	if (how_To == true)
	{
		howToPlay();
	}
	else {

		//dim background and show pause sign
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
		CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //for dimming pause menu

		CP_Settings_Fill(CP_Color_Create(240, 230, 140, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);// for pause menu

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, WINDOW_HEIGHT / 2.4f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);// for menu button

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, WINDOW_HEIGHT / 1.9f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);// for how to play button

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Main Menu", WINDOW_WIDTH / 2.3f, WINDOW_HEIGHT / 2.11f);
		CP_Font_DrawText("How To Play", WINDOW_WIDTH / 2.33f, WINDOW_HEIGHT / 1.72f);
		CP_Image_Draw(pause_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f, 100.0f, 100.0f, 255);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Press escape key to continue!", WINDOW_WIDTH / 3.0f, WINDOW_HEIGHT / 1.4f);

		//return to mainmenu
		if (IsAreaClicked(WINDOW_WIDTH / 1.99f, WINDOW_HEIGHT / 2.18f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
		}
		//Go to how To Play screen
		else if (IsAreaClicked(WINDOW_WIDTH / 1.99f, WINDOW_HEIGHT / 1.76f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			how_To = true;
			page = 1;
		}
	}
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
}

void howToPlay(void)
{
	//dim background and show pause sign
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //for dimming pause menu

	CP_Settings_Fill(CP_Color_Create(240, 230, 140, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 6.0f, WINDOW_WIDTH / 1.5f, WINDOW_HEIGHT / 1.5f);// for pause menu

	if (page == 1)
	{
		CP_Settings_TextSize(30.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Movement controls: W - Up | S - Down | A - Left | D - Right", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.8f);
		CP_Font_DrawText("Attack controls: Mouse left click - Charge Mana", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.5f);
		CP_Font_DrawText("Special ability: Space - Spell Selection between Fire and Ice", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.24f);
		CP_Font_DrawText("Fire deals Damage to enemies ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.08f);
		CP_Font_DrawText("Ice freezes the enemy but doesnt damage them ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.95f);
		CP_Font_DrawText("Enter the doors that are open. Once you enter a room, ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.60f);
		CP_Font_DrawText("the previous room is blocked off. ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.53f);

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect((WINDOW_WIDTH / 2.8f) * 1.66, (WINDOW_HEIGHT / 4.0f) * 2.75f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for next page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //next page triangle
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 2.82f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 3.02f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.78f, (WINDOW_HEIGHT / 4.0f) * 2.91 // Tip vertex
		);

		//next page
		if (IsAreaClicked((WINDOW_WIDTH / 2.8f) * 1.725, (WINDOW_HEIGHT / 4.0f) * 2.9f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 2;
		}

	}
	else if (page == 2)
	{
		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.8f, (WINDOW_HEIGHT / 4.0f) * 2.75f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for prev page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //prev page triangle
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 2.82f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 3.02f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.02f, (WINDOW_HEIGHT / 4.0f) * 2.91f  // Tip vertex
		);

		CP_Settings_TextSize(30.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("There are two enemy types,", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.8f);
		CP_Font_DrawText("Blue chases the player, Red shoots with projectiles", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.5f);
		CP_Font_DrawText("Avoid touching the enemies as it'll damage you", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 2.24f);
		CP_Font_DrawText("When enemies dies, Players score increases, ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.90f);
		CP_Font_DrawText("There is also a chance that enemy drop items. ", WINDOW_WIDTH / 3.8f, WINDOW_HEIGHT / 1.78f);
		item_x = (WINDOW_WIDTH / 4.0f);
		item_y = (WINDOW_HEIGHT / 1.65f);
		int gap = 140;

		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Heal", item_x-25, item_y+40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("AtkUp", item_x - 35, item_y + 40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("MovSpdUp", item_x - 60, item_y + 40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("CldwnSpdUp", item_x - 60, item_y + 40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(255, 255, 107, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("AtkSpd", item_x - 40, item_y + 40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(90, 34, 139, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("ManaBldSpd", item_x - 75, item_y + 40);

		item_x += gap;
		CP_Settings_Fill(CP_Color_Create(249, 105, 14, 255));
		CP_Graphics_DrawTriangle(item_x, item_y - 20, item_x - 20, item_y + 10, item_x + 20, item_y + 10);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("AtkSizeUp", item_x - 55, item_y + 40);

		//prev page
		if (IsAreaClicked((WINDOW_WIDTH / 2.63f), (WINDOW_HEIGHT / 4.0f) * 2.9f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 1;
		}
	}

	CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, (WINDOW_HEIGHT / 4.0f)*2.75f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);// return to pause menu button

	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("How to play", WINDOW_WIDTH / 2.3f, WINDOW_HEIGHT / 4.0f);
	CP_Font_DrawText("Back", WINDOW_WIDTH / 2.1f, (WINDOW_HEIGHT / 4.0f) * 2.98f);
	//return to mainmenu
	if (IsAreaClicked(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT / 4.0f) * 2.9f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
		CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		how_To = false;
	}
}
