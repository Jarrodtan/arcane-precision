#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "startmenu.h"
#include "stdbool.h"
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
CP_Font myFont;
float textSize;
int saveSlot;
bool isNewGame;

extern const char *saveFile1;
extern const char *saveFile2;

void Main_Menu_Init(void)
{
    CP_Settings_RectMode(CP_POSITION_CENTER);
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    textSize = 50.0f;
    CP_Settings_TextSize(textSize);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
}

void Main_Menu_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));


    //save slot1
    CP_Font_Set(myFont);
    switch (checkSaveExists(saveFile1))
    {
    case 1:
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f,
            WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 12.0f);
        CP_Graphics_DrawRect((WINDOW_WIDTH / 4.0f)*2.89, WINDOW_HEIGHT / 3.0f,
            WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 12.0f);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Load existing save", WINDOW_WIDTH / 2.555f, WINDOW_HEIGHT / 2.91f);
        CP_Font_DrawText("Delete", (WINDOW_WIDTH / 4.05f) * 2.76, WINDOW_HEIGHT / 2.91f);

        break;
    case 0:
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);    
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("New game", WINDOW_WIDTH / 2.29f, WINDOW_HEIGHT / 2.91f);
        break;
    }
    //delete button
    if (IsAreaClicked((WINDOW_WIDTH / 4.0f) * 2.89, WINDOW_HEIGHT / 3.0f,
        WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        remove(saveFile1);
    }
    //start button
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 3.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        switch (checkSaveExists(saveFile1))
        {
        case 1:
            isNewGame = false;
            break;
        case 0:
            isNewGame = true;
            break;
        }
        saveSlot = 1;
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }    


    //save slot 2
    CP_Font_Set(myFont);
    switch (checkSaveExists(saveFile2))
    {
    case 1:
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        //load game button
        CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
            WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 12.0f);
        //delete save button
        CP_Graphics_DrawRect((WINDOW_WIDTH / 4.0f)*2.89, WINDOW_HEIGHT / 2.0f,
            WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 12.0f);

        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("Load existing save", WINDOW_WIDTH / 2.555f, WINDOW_HEIGHT / 1.95f);
        CP_Font_DrawText("Delete", (WINDOW_WIDTH / 4.05f) * 2.76, WINDOW_HEIGHT / 1.95f);
        break;
    case 0:
        CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
        CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
            WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("New game", WINDOW_WIDTH / 2.30f, WINDOW_HEIGHT / 1.95f);
        break;
    }
    //delete button
    if (IsAreaClicked((WINDOW_WIDTH / 4.0f) * 2.89, WINDOW_HEIGHT / 2.0f,
        WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        remove(saveFile2);
    }
    //start button
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {

        switch (checkSaveExists(saveFile2))
        {
        case 1:
            isNewGame = false;
            break;
        case 0:
            isNewGame = true;
            break;
        }
        saveSlot = 2;
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }

    
    //Back button
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Back", WINDOW_WIDTH / 2.12f, WINDOW_HEIGHT / 1.48f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f,
        WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
    }

}

void Main_Menu_Exit(void)
{

}