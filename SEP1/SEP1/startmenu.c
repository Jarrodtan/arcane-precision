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

CP_Sound* backgroundMusic = NULL;
float musicVolume = 0.5;
bool musicPlaying = false;

void Start_Menu_Init(void)
{
    CP_Settings_RectMode(CP_POSITION_CENTER);
    myFont = CP_Font_Load("Assets/high-tower-text.ttf");
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

    if (backgroundMusic == NULL) {
        backgroundMusic = CP_Sound_Load("Assets/Music/menuMusic.mp3");
    }

    musicPlaying = false;
}

void Start_Menu_Update(void)
{
    // Draw background image
    CP_Image backgroundImage = CP_Image_Load("Assets/Arcane_Precision_BG_Final.png");
    CP_Image_Draw(backgroundImage, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT,255);

    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

    //Play game button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 3.0f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Play Game", WINDOW_WIDTH / 12.0f, WINDOW_HEIGHT / 2.86f);
    if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 3.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
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
        CP_Engine_SetNextGameState(Leaderboard_Init, Leaderboard_Update, Leaderboard_Exit);
    }

    //Exit button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Exit", WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 1.47f);
    if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_Terminate();
    }

    //Credits button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.2f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Credits", WINDOW_WIDTH / 9.5f, WINDOW_HEIGHT / 1.18f);
    if (IsAreaClicked(WINDOW_WIDTH / 6.5f, WINDOW_HEIGHT / 1.2f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);
    }

    // Settings button
    CP_Image settingbuttonIcon = CP_Image_Load("Assets/settings_icon.png"); 
    CP_Image_Draw(settingbuttonIcon,WINDOW_WIDTH - 90.0f, WINDOW_HEIGHT - 60.0f,
        WINDOW_WIDTH / 15.0f, WINDOW_HEIGHT / 17.0f,255);
    if (IsAreaClicked(WINDOW_WIDTH - 90.0f, WINDOW_HEIGHT - 50.0f,
        WINDOW_WIDTH / 15.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(settingsscreen_Init, settingsscreen_Update, settingsscreen_Exit);
    }

    // plays music
    if (!musicPlaying)
    {
        CP_Sound_StopGroup(CP_SOUND_GROUP_0);
        CP_Sound_PlayAdvanced(backgroundMusic, musicVolume, 1, TRUE, CP_SOUND_GROUP_0);
        musicPlaying = true;
    }

}

void Start_Menu_Exit(void)
{
    
}
