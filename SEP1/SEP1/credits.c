//---------------------------------------------------------
// file:	credits.c
// author:	[Tan Wei Leong]
// email:	[weileong.tan@digipen.edu]
//
// brief:	credits.c displays a image of the credits.
//
// Copyright © 2024 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "cprocessing.h"
#include "stdio.h"
#include "startmenu.h"
#include "utils.h"
#include "stdbool.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f

extern CP_Font myFont;
extern bool creditsScreen;
float textSize;
int page;
bool Credits_Pg1;


void Credits(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

    // Credits
    CP_Image Credits = CP_Image_Load("Assets/Credits_page.png");
    CP_Image_Draw(Credits, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 255);

    // Back button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 1.15f, WINDOW_HEIGHT / 6.0f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(50.0f);
    CP_Font_DrawText("Back", WINDOW_WIDTH / 1.19f, WINDOW_HEIGHT / 5.5f);
    if (IsAreaClicked(WINDOW_WIDTH / 1.15f, WINDOW_HEIGHT / 6.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        creditsScreen = false;
    }
}

