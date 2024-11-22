
#ifndef OBSTACLE_H
#define OBSTACLE_H
#define MAX_OBSTACLES 10
CP_Vector obstacle[MAX_OBSTACLES];

#include <stdbool.h> // Include for bool type
#include "cprocessing.h"



//extern CP_Vector obstacle[MAX_OBSTACLES];
//extern int currentObstacleCount;
//extern int lastRoom;
//extern int obstacle_diameter;

//bool IsOverlapping(float x, float y, float diameter);
void InitializeObstacle(int index);
bool CheckCollision(CP_Vector player_position, float playerDiameter, CP_Vector obstacle, float obstacleSize);
void HandleCollision(CP_Vector* player_position, float playerDiameter, CP_Vector obstacle, float obstacleSize);
bool CheckEnemyCollision(CP_Vector enemy_position, float enemyDiameter, CP_Vector obstacle, float obstacleSize);
void HandleEnemyCollision(CP_Vector* enemy_position, float enemyDiameter, CP_Vector obstacle, float obstacleSize);

bool CheckBulletCollision(CP_Vector bullet_position, float bulletDiameter, CP_Vector obstacle, float obstacleSize);
void HandleProjectileCollision(struct enemyAttack* bullet);
bool CheckPlayerBulletCollision(CP_Vector playerBullet_position, float playerBulletDiameter, CP_Vector obstacle, float obstacleSize);
void HandlePlayerProjectileCollision(struct playerAttack* bullet[]);
void UpdateObstacles(int roomsPassed, CP_Vector player_position, float playerDiameter);

#endif // OBSTACLE_H
