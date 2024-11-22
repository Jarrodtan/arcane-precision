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

    // Title: Credits
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 140, 180, 255));
    CP_Settings_TextSize(100.0f);
    CP_Font_DrawText("Credits", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 6.0f); // Find a way to bold

    // Names
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 200, 0, 255));
    CP_Settings_TextSize(60.0f);
    CP_Font_DrawText("Khor Ee Ling", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 3.5f);
    CP_Font_DrawText("Toh Jing Han", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 2.8f);
    CP_Font_DrawText("Tan Che Fong", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 2.3f);
    CP_Font_DrawText("Tan Wei Leong", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 1.95f);
    CP_Font_DrawText("Beverley Choy", WINDOW_WIDTH / 2.45f, WINDOW_HEIGHT / 1.7f);
    CP_Image digipenLogo = CP_Image_Load("Assets/DigiPen_BLACK.png");
    CP_Image_Draw(digipenLogo, WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT / 3.0f) * 2.1f, 450.0f, 150.0f, 255);

    // Back button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.2f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(50.0f);
    CP_Font_DrawText("Back", WINDOW_WIDTH / 2.13f, WINDOW_HEIGHT / 1.18f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.2f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
    }
}

void Credits_Exit(void)
{

}
