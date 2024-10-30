#include <math.h>
#include "cprocessing.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"

bool isNewGame;

typedef struct {
    float moveSpeed;
    int maxLives;
    int currentLives;
    float manaBuildSpeed;
    float cooldownSpeed;
    float attackDamage;
    float attackSize;
    float attackSpeed;
    int roomsPassed;
}playerStats;

const char* saveFilePath = "player_save.dat";

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
    if (click_x < (area_center_x + area_width / 2) && click_x >(area_center_x - area_width / 2) && click_y < (area_center_y + area_height / 2) && click_y >(area_center_y - area_height / 2))
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

int rectAreIntersecting(float s1_x, float w1, float s2_x, float w2)
{
    if (s1_x+w1 >= s2_x && s1_x <= s2_x+w2) {
        return 1;
    }
    else {
        return 0;
    }
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


void savePlayerStats(playerStats* stats) {
    FILE *file = fopen(saveFilePath, "wb");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    fwrite(stats, sizeof(playerStats), 1, file);
    fclose(file);

    printf("Player stats saved!\n");
}

// Function to load player stats from a file
void loadPlayerStats(playerStats* stats) {
    
    FILE *file = fopen(saveFilePath, "rb");
    if (file == NULL) {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    fread(stats, sizeof(playerStats), 1, file);
    fclose(file);

    printf("%f\n", stats->attackDamage);
    printf("%f\n", stats->attackSize);
    printf("%f\n", stats->attackSpeed);
    printf("Player stats loaded!\n");
}
