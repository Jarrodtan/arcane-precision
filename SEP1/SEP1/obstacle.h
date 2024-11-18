
#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <stdbool.h> // Include for bool type
#include "cprocessing.h"



//extern CP_Vector obstacle[MAX_OBSTACLES];
//extern int currentObstacleCount;
//extern int lastRoom;
//extern int obstacle_diameter;

//bool IsOverlapping(float x, float y, float diameter);
void InitializeObstacle(int index);
bool CheckCollision(CP_Vector player_position, float playerDiameter, CP_Vector obstacle, int obstacleSize);
void HandleCollision(CP_Vector* player_position, float playerDiameter, CP_Vector obstacle, int obstacleSize);
bool CheckEnemyCollision(CP_Vector enemy_position, float enemyDiameter, CP_Vector obstacle, int obstacleSize);
void HandleEnemyCollision(CP_Vector* enemy_position, float enemyDiameter, CP_Vector obstacle, int obstacleSize);
void UpdateObstacles(int roomsPassed, CP_Vector player_position, float playerDiameter);

#endif // OBSTACLE_H
