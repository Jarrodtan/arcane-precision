#include "cprocessing.h"
#include "stdio.h"
#include "startmenu.h"
#include "utils.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

extern CP_Font myFont;
float textSize;
void Credits_Init(void)
{
    CP_Settings_RectMode(CP_POSITION_CENTER);
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
}

void Credits_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

    // Credits
    CP_Image Credits = CP_Image_Load("Assets/Credits_page.png");
    CP_Image_Draw(Credits, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f , WINDOW_WIDTH, WINDOW_HEIGHT, 255);

    // Back button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 1.2f, WINDOW_HEIGHT / 6.0f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(50.0f);
    CP_Font_DrawText("Back", WINDOW_WIDTH / 1.24f, WINDOW_HEIGHT / 5.5f);
    if (IsAreaClicked(WINDOW_WIDTH / 1.2f, WINDOW_HEIGHT / 6.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
    }
}

void Credits_Exit(void)
{

}
