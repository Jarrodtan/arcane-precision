#pragma once

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

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int manaAreIntersecting(float s1_x, float w1, float s2_x, float w2);
int doorIntersect(float p_x, float p_y, float p_dia, float door_x, float door_y, float door_width, float door_height);
void drawHearts(float x, float y, float size);
void savePlayerStats(playerStats *stats, const char* saveFileName);
void loadPlayerStats(playerStats *stats, const char* saveFileName);
int checkSaveExists(const char* saveFileName);
