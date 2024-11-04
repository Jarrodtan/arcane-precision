#include <math.h>
#include "cprocessing.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"

bool newGame;

typedef struct {
    float moveSpeed;
    int lives;
    float manaBuildSpeed;
    float cooldownSpeed;
    float attackDamage;
    float attackSize;
    float attackSpeed;
    int score;
    int roomsPassed;
}playerStats;

const char* saveFile1 = "save1.dat";
const char* saveFile2 = "save2.dat";


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
    if (click_x < (area_center_x + area_width / 2) && click_x >(area_center_x - area_width / 2) && click_y < (area_center_y + area_height / 2) && click_y > (area_center_y - area_height / 2))
    {
        if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
        {
            return 1;
        }
    }
    else {
        return 0;
    }
    return 0;
}

int manaAreIntersecting(float s1_x, float w1, float s2_x, float w2)
{
    if (s1_x+w1 >= s2_x && s1_x <= s2_x+w2) {
        return 1;
    }
    else {
        return 0;
    }
}

int doorIntersect(float p_x, float p_y, float p_dia, float door_x, float door_y, float door_width, float door_height)
{
    float player_diameter = (p_dia / 2)+10;

    if (p_x + player_diameter >= door_x && p_x - player_diameter <= door_x + door_width && 
        p_y + player_diameter >= door_y && p_y - player_diameter <= door_y + door_height)
    {
        return 1;
    }
    return 0;
}

void drawHearts(float x, float y, float size) {
    //Player Hearts
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));

    // Draw heart using vertices
    CP_Graphics_BeginShape();
    CP_Graphics_AddVertex(x - size, y); // Left corner
    CP_Graphics_AddVertex(x - size * 0.5f, y - size * 0.5f); // Top left
    CP_Graphics_AddVertex(x, y); // Center top
    CP_Graphics_AddVertex(x + size * 0.5f, y - size * 0.5f); // Top right
    CP_Graphics_AddVertex(x + size, y); // Right corner
    CP_Graphics_AddVertex(x, y + size * 1.5f); // Bottom point
    CP_Graphics_EndShape();
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
    float distance = CP_Math_Distance(c1_x, c1_y, c2_x, c2_y);
    if (distance <= (r1 / 2 + r2 / 2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

void savePlayerStats(playerStats* stats, const char* saveFileName) {
    FILE *file = fopen(saveFileName, "wb");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    fwrite(stats, sizeof(playerStats), 1, file);
    fclose(file);
}

// Function to load player stats from a file
void loadPlayerStats(playerStats* stats, const char* saveFileName) {
    
    FILE *file = fopen(saveFileName, "rb");
    if (file == NULL) {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    fread(stats, sizeof(playerStats), 1, file);
    fclose(file);
}

int checkSaveExists(const char* saveFileName)
{
FILE* file = fopen(saveFileName, "rb");
if (file != NULL) {
    fclose(file);
    return 1;
}
return 0;
}
