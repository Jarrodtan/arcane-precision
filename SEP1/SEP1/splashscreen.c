#include "cprocessing.h"
#include "startmenu.h"
#include "stdbool.h"
#include <windows.h> // For Sleep function

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

CP_Image splashImage;
static bool splashDrawn = false;
static float splashStartTime;

void splashscreen_Init(void)
{
    // Load image
    splashImage = CP_Image_Load("Assets/DigiPen_splashscreen.png");
    // Record the start time
    splashStartTime = CP_System_GetMillis();
}

void splashscreen_Update(void)
{
    CP_Image_Draw(splashImage, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
    // Calculate the time since the splash screen was displayed
    float elapsedTime = CP_System_GetMillis() - splashStartTime;

    // If 2 seconds (2000 milliseconds) have passed, transition to the start menu
    if (elapsedTime >= 2000.0f)
    {
        CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
    }
}

void splashscreen_Exit(void)
{
    // Free the splash screen image
    CP_Image_Free(&splashImage);
}
