#include "obstacle.h"
#include <stdio.h>
#include "cprocessing.h"
#include <stdbool.h> // Include for bool type
#include "mainmenu.h"
#include "stdlib.h"
#include "utils.h"
#include "game.h"
#include <math.h>

#define MAX_OBSTACLES 10
CP_Vector obstacle[MAX_OBSTACLES]; // obstacle for random spawn
int currentObstacleCount = 3;
int lastRoom = -1; // Initialize to an invalid room number
float obstacle_diameter = 110.0f;
extern struct player player;

void InitializeObstacle(int index) {
    float xRange, yRange;
    float dx, dy, distance, bufferDistance;
    do {
        xRange = CP_Random_RangeFloat(150, 1300);
        yRange = CP_Random_RangeFloat(150, 700);
        dx = player.position.x - xRange;
        dy = player.position.y - yRange;
        distance = (float)sqrt(dx * dx + dy * dy);
        bufferDistance = player.diameter + 100;
    } while (distance < bufferDistance); // Regenerate if too close

    obstacle[index].x = xRange;
    obstacle[index].y = yRange;
}

bool CheckCollision(CP_Vector player_position, float playerDiameter, CP_Vector obstacle, int obstacleSize) {
    float playerRadius = playerDiameter / 2.0f;
    float playerLeft = player_position.x - playerRadius;
    float playerRight = player_position.x + playerRadius;
    float playerTop = player_position.y - playerRadius;
    float playerBottom = player_position.y + playerRadius;

    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;

    return playerRight > obstacleLeft && playerLeft < obstacleRight &&
        playerBottom > obstacleTop && playerTop < obstacleBottom;
}

void HandleCollision(CP_Vector* player_position, float playerDiameter, CP_Vector obstacle, int obstacleSize) {
    float playerRadius = playerDiameter / 2.0f;
    float playerLeft = player_position->x - playerRadius;
    float playerRight = player_position->x + playerRadius;
    float playerTop = player_position->y - playerRadius;
    float playerBottom = player_position->y + playerRadius;

    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;

    float overlapLeft = playerRight - obstacleLeft;
    float overlapRight = obstacleRight - playerLeft;
    float overlapTop = playerBottom - obstacleTop;
    float overlapBottom = obstacleBottom - playerTop;

    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;

    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;

    if (minOverlapX < minOverlapY) {
        player_position->x += fromLeft ? -minOverlapX : minOverlapX;
    }
    else {
        player_position->y += fromTop ? -minOverlapY : minOverlapY;
    }
}

void UpdateObstacles(int roomsPassed, CP_Vector player_position, float playerDiameter) {
    // Update the number of obstacles based on the number of rooms
    // Check if the player has entered a new room
    if (lastRoom != roomsPassed) {
        // Randomly generate the number of obstacles within the range 3 to 10
        int newObstacleCount = CP_Random_RangeInt(3, 10);
        // Initialize new obstacles if the count has increased
        for (int i = currentObstacleCount; i < newObstacleCount; i++) {
            InitializeObstacle(i);
        }
        currentObstacleCount = newObstacleCount;
        lastRoom = roomsPassed; // Update the last room to the current room
    }

    // Obstacle Spawn
    for (int i = 0; i < currentObstacleCount; i++) {
        CP_Settings_Fill(CP_Color_Create(150, 255, 100, 255));
        CP_Graphics_DrawRect(obstacle[i].x, obstacle[i].y, obstacle_diameter, obstacle_diameter);
    }
}
