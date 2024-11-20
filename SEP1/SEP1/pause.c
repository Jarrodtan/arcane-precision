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
CP_Image tut_page1, tut_page2;
bool game_pause;
bool how_To;
extern CP_Font myFont;
extern bool tut;
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
		CP_Font_DrawText("How To Play", WINDOW_WIDTH / 2.33f, WINDOW_HEIGHT / 2.11f);
		CP_Font_DrawText("Main Menu", WINDOW_WIDTH / 2.3f, WINDOW_HEIGHT / 1.72f);
		CP_Image_Draw(pause_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f, 100.0f, 100.0f, 255);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Press escape key to continue!", WINDOW_WIDTH / 3.0f, WINDOW_HEIGHT / 1.4f);

		//return to mainmenu
		if (IsAreaClicked(WINDOW_WIDTH / 1.99f, WINDOW_HEIGHT / 2.18f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			how_To = true;
			page = 1;
		}
		//Go to how To Play screen
		else if (IsAreaClicked(WINDOW_WIDTH / 1.99f, WINDOW_HEIGHT / 1.76f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
		}
	}
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 50));
}

void howToPlay(void)
{
	//dim background
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //for dimming pause menu

	if (page == 1)
	{
		CP_Image_Draw(tut_page1, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1065.0f, 600.0f, 255);

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect((WINDOW_WIDTH / 2.8f) * 1.66, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for next page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //next page triangle
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 3.42f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 3.62f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.78f, (WINDOW_HEIGHT / 4.0f) * 3.52f // Tip vertex
		);

		//next page
		if (IsAreaClicked((WINDOW_WIDTH / 2.8f) * 1.725, (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 2;
		}

	}
	else if (page == 2)
	{
		
		CP_Image_Draw(tut_page2, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1065.0f, 600.0f, 255);
		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.8f, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for prev page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //prev page triangle
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 3.42f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 3.62f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.02f, (WINDOW_HEIGHT / 4.0f) * 3.52f  // Tip vertex
		);

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);// return to pause menu button
		CP_Settings_TextSize(50.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Back", WINDOW_WIDTH / 2.11f, (WINDOW_HEIGHT / 4.0f) * 3.56f);
		//return to mainmenu
		if (IsAreaClicked(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			how_To = false;
		}
		//prev page
		if (IsAreaClicked((WINDOW_WIDTH / 2.63f), (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 1;
		}
	}
	
}

void tutorial(void)
{
	//dim background and show pause sign
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //for dimming pause menu

	if (page == 1)
	{
		
		CP_Image_Draw(tut_page1, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1065.0f, 600.0f, 255);

		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect((WINDOW_WIDTH / 2.8f) * 1.66, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for next page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //next page triangle
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 3.42f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.69f, (WINDOW_HEIGHT / 4.0f) * 3.62f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.78f, (WINDOW_HEIGHT / 4.0f) * 3.52f // Tip vertex
		);

		//next page
		if (IsAreaClicked((WINDOW_WIDTH / 2.8f) * 1.725, (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 2;
		}


	}
	else if (page == 2)
	{
		
		CP_Image_Draw(tut_page2, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 1065.0f, 600.0f, 255);
		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.8f, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f);// button for prev page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangle( //prev page triangle
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 3.42f, // Top vertex
			(WINDOW_WIDTH / 2.8f) * 1.11f, (WINDOW_HEIGHT / 4.0f) * 3.62f, // Bottom vertex
			(WINDOW_WIDTH / 2.8f) * 1.02f, (WINDOW_HEIGHT / 4.0f) * 3.52f  // Tip vertex
		);
		//return to mainmenu
		CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
		CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);// return to pause menu button
		CP_Settings_TextSize(50.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("Back", WINDOW_WIDTH / 2.11f, (WINDOW_HEIGHT / 4.0f) * 3.56f);
		//return to mainmenu
		if (IsAreaClicked(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			tut = false;
		}
		//prev page
		if (IsAreaClicked((WINDOW_WIDTH / 2.63f), (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 12.0f,
			CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
		{
			page = 1;
		}
	}
	
}
