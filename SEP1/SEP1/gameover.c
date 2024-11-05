#include "cprocessing.h"
#include "startmenu.h"
#include "utils.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

CP_Font myFont;
CP_Image gameover_sign;

float textSize;

void gameover_Init(void)
{
	gameover_sign = CP_Image_Load("Assets/Gameover.png");
	CP_Settings_RectMode(CP_POSITION_CENTER);
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	textSize = 50.0f;
	CP_Settings_TextSize(textSize);
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
}

void gameover_Update(void)
{
	// Testing Gameover sign
	CP_Image_Draw(gameover_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	
	//Back button
	CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.2f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Back", WINDOW_WIDTH / 2.13f, WINDOW_HEIGHT / 1.18f);
	if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.2f,
		WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
	}
}

void gameover_Exit(void)
{

}
