#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include "utils.h"
#include "pause.h"
#include "stdbool.h"
#include "startmenu.h"

CP_Image pause_sign;
bool game_pause;

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

void pause(void) 
{
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

		CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
	}
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
}