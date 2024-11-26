#include <cprocessing.h>
#include <stdbool.h>
#include "startmenu.h"
#include "settingsmenu.h"
#include "utils.h"
#include "game.h"
#include "pause.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

CP_Font myFont;
float textSize;
float musicVolume = 0.5;
extern bool settings;


void setVolume(float newVolume) // change volume based on slider
{
    musicVolume = CP_Math_ClampFloat(newVolume, 0.0f, 1.0f);
    CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, musicVolume); // set music volume
}

void settingsScreen(void)
{
    CP_Settings_RectMode(CP_POSITION_CORNER);
    //myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    //textSize = 50.0f;
    //CP_Settings_TextSize(textSize);
    //CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
    //CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
    CP_Graphics_ClearBackground(CP_Color_Create(6, 38, 38, 0));

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
    CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //for dimming pause menu

    CP_Settings_Fill(CP_Color_Create(240, 230, 140, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);// for pause menu

 
    CP_Settings_Fill(CP_Color_Create(255, 168, 5, 255));
    CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, (WINDOW_HEIGHT / 4.0f) * 3.35f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
    CP_Font_Set(myFont);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Back", WINDOW_WIDTH / 2.13f, (WINDOW_HEIGHT / 4.0f) * 3.56f);
    if (IsAreaClicked(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT / 4.0f) * 3.52f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f,
        CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
    {
        settings = false;
    }

    CP_Font_DrawText("Adjust Music Volume", WINDOW_WIDTH/2.80f, WINDOW_HEIGHT/2.3f);

    float sliderX = WINDOW_WIDTH / 2.8f;
    float sliderY = WINDOW_HEIGHT/2.5f + ((WINDOW_HEIGHT / 2.0f)/4.0f);
    float sliderWidth = (WINDOW_WIDTH/1.75f)/2.0f;
    float sliderHeight = 20.0f;
    float handleRadius = 10.0f;

    // volume slider
    CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
    CP_Graphics_DrawRect(sliderX, sliderY, sliderWidth, sliderHeight);

    float handleX = sliderX + (musicVolume * sliderWidth);
    float handleY = sliderY;
    CP_Settings_Fill(CP_Color_Create(100, 100, 250, 255));
    CP_Graphics_DrawCircle(handleX, sliderY + (sliderHeight / 2.0f), handleRadius); // draw volume slider indicator based on position


    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
        if (CP_Input_GetMouseY() >= sliderY - sliderHeight / 2.0f && CP_Input_GetMouseY() <= sliderY + sliderHeight + handleRadius) {
            if (CP_Input_GetMouseX() >= sliderX && CP_Input_GetMouseX() <= sliderX + sliderWidth) {
                float newVolume = (CP_Input_GetMouseX() - sliderX) / sliderWidth; // Calculate volume based on mouse position
                setVolume(newVolume);
            }
        }
    }
}
