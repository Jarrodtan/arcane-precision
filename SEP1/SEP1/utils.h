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
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int AreIntersecting(float s1_x, float w1, float s2_x, float w2);
void drawHearts(float x, float y, float size);
void savePlayerStats(playerStats *stats);
void loadPlayerStats(playerStats *stats);