#pragma once

typedef struct {
    float moveSpeed;
    int lives;
    float manaBuildSpeed;
    float cooldownSpeed;
    int attackDamage;
    float attackSize;
    float attackSpeed;
    int score;
    int roomsPassed;
    int difficulty;
    int lastEntered;
    float hitboxSize;
}playerStats;

typedef struct {
    char playerName[256];
    int score;
}leaderboard;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int manaAreIntersecting(float s1_x, float w1, float s2_x, float w2);
int doorIntersect(float p_x, float p_y, float p_dia, float door_x, float door_y, float door_width, float door_height);
void drawHearts(float x, float y, float size);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
void saveLeaderboard(leaderboard ldrboard[], int count, const char* ldrSave);
int loadLeaderboard(leaderboard ldrboard[], const char* ldrSave);
int compareScores(const void* a, const void* b);
void updateLeaderboard(leaderboard ldrboard[], int* count, const char* playerName, int playerScore, const char* ldrSave);
void savePlayerStats(playerStats *stats, const char* saveFileName);
void loadPlayerStats(playerStats *stats, const char* saveFileName);
int checkSaveExists(const char* saveFileName);
