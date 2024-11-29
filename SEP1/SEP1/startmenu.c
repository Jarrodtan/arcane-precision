//---------------------------------------------------------
// file:	startmenu.c
// author:	[Tan Wei Leong]
// email:	[weileong.tan@digipen.edu]
//
// brief:	startmenu.c is the screen thats shown after the splashscreen.
//
// Copyright © 2024 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "credits.h"
#include "leaderboard.h"
#include "settingsmenu.h"
#include <stdbool.h>
#include "startmenu.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

CP_Font myFont;
float textSize;
const char *mainBGMFile = "Assets/Music/menuMusic.mp3";
CP_Sound backgroundMusic = NULL;

bool musicPlaying;
bool settings;
bool leaderboardScreen;
bool creditsScreen;
bool newLoadScreen;
extern float musicVolume;

void Start_Menu_Init(void)
{
    CP_Settings_RectMode(CP_POSITION_CENTER);
    myFont = CP_Font_Load("Assets/high-tower-text.ttf");
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

    if (backgroundMusic == NULL) {
        backgroundMusic = CP_Sound_Load(mainBGMFile);
    }

    settings = false;
    leaderboardScreen = false;
    creditsScreen = false;
    newLoadScreen = false;
}

void Start_Menu_Update(void)
{
    if (settings == true)
    {
        settingsScreen();
    }
    else if (leaderboardScreen == true)
    {
        Leaderboard();
    }
    else if (creditsScreen == true)
    {
        Credits();
    }
    else if (newLoadScreen == true)
    {
        newGameLoadGame();
    }
    else
    {
        CP_Settings_RectMode(CP_POSITION_CENTER);

        // Draw background image
        CP_Image backgroundImage = CP_Image_Load("Assets/Arcane_Precision_BG_Final.png");
        CP_Image_Draw(backgroundImage, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 255);

        CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

        //Play game button
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 3.0f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
        CP_Font_Set(myFont);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Start Game", WINDOW_WIDTH / 12.6f, WINDOW_HEIGHT / 2.86f);
        if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 3.0f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
            newLoadScreen = true;
        }

        //Leaderboard button
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 2.0f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
        CP_Font_Set(myFont);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Leaderboard", WINDOW_WIDTH / 13.5f, WINDOW_HEIGHT / 1.94f);
        if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 2.0f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
            leaderboardScreen = true;
        }

        //Exit button
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.5f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
        CP_Font_Set(myFont);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Credits", WINDOW_WIDTH / 9.5f, WINDOW_HEIGHT / 1.47f);
        if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.5f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
            creditsScreen = true;
        }

        //Credits button
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.2f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
        CP_Font_Set(myFont);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Quit Game", WINDOW_WIDTH / 12.5f, WINDOW_HEIGHT / 1.18f);
        if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.2f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
             CP_Engine_Terminate();
        }

        // Settings button
        CP_Image settingbuttonIcon = CP_Image_Load("Assets/settings_icon.png");
        CP_Image_Draw(settingbuttonIcon, WINDOW_WIDTH - 120.0f, WINDOW_HEIGHT - 120.0f,
            WINDOW_WIDTH / 15.0f, WINDOW_HEIGHT / 9.0f, 255);
        if (IsAreaClicked(WINDOW_WIDTH - 120.0f, WINDOW_HEIGHT - 100.0f,
            WINDOW_WIDTH / 15.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
            settings = true;

        }

        // plays music
        if (!musicPlaying)
        {
            CP_Sound_StopGroup(CP_SOUND_GROUP_0);
            CP_Sound_PlayAdvanced(backgroundMusic, musicVolume, 1, TRUE, CP_SOUND_GROUP_0); // set music volume, pitch and loop
            musicPlaying = true;
        }
    }
}

void Start_Menu_Exit(void)
{
    musicPlaying = false;
}
