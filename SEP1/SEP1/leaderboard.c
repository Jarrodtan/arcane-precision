#include "cprocessing.h"
#include "startmenu.h"
#include "utils.h"
#include "stdio.h"
#include "string.h"
#include "game.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_LEADERBOARD 10

CP_Font myFont;

float textSize;
extern struct player player;
extern const char* leaderboardSave;

int count;
float startX;
float startY;
float lineSpacing;
leaderboard ldrboard[MAX_LEADERBOARD];

void Leaderboard_Init(void)
{
    CP_Settings_RectMode(CP_POSITION_CENTER);
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

    count = loadLeaderboard(ldrboard, leaderboardSave);

    // Define starting position and spacing between leaderboard entries
    startX = WINDOW_WIDTH / 2.68f;
    startY = WINDOW_HEIGHT / 8.5f;  // Start higher on the screen
    lineSpacing = textSize + 20.0f; // Space between each entry line

}


void Leaderboard_Update(void)
{


    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

    CP_Settings_Fill(CP_Color_Create(240, 230, 140, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.25f, WINDOW_WIDTH / 3.5f, WINDOW_HEIGHT / 1.25f);

    // Iterate over each leaderboard entry and display it
    for (int i = 0; i < count; i++) {
        char entryText[256];

        // Format the leaderboard entry as "Rank. Name - Score"
        sprintf_s(entryText, sizeof(entryText), "%d. %s - %d", i + 1, ldrboard[i].playerName, ldrboard[i].score);

        // Set text color to white and draw the leaderboard entry
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText(entryText, startX, startY + i * lineSpacing);
    }

    //Back button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.075f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Back", WINDOW_WIDTH / 2.13f, WINDOW_HEIGHT / 1.065f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.075f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
    }
}

void Leaderboard_Exit(void)
{

}
