#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
CP_Font myFont;
float textSize;
void Main_Menu_Init(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));
    CP_Settings_RectMode(CP_POSITION_CENTER);
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
}

void Main_Menu_Update(void)
{
    //Start button
    CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 6.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Play", WINDOW_WIDTH / 2.10f, WINDOW_HEIGHT / 4.9f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 6.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }

    //Exit button
    CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 6.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Exit", WINDOW_WIDTH / 2.10f, WINDOW_HEIGHT / 1.5f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 6.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_Terminate();
    }
}

void Main_Menu_Exit(void)
{

}