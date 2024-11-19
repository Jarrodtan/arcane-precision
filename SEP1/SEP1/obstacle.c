#include <stdio.h>
#include <stdbool.h> // Include for bool type
#include <math.h>
#include "stdlib.h"
#include "cprocessing.h"
#include "mainmenu.h"
#include "game.h"
#include "utils.h"
#include "obstacle.h"
#include "enemy.h"

 // obstacle for random spawn
int currentObstacleCount = 3;
int lastRoom = -1; // Initialize to an invalid room number
float obstacle_diameter = 110.0f;

//for enemy and player collision
extern struct enemy enemyStationary;
extern struct enemy enemyMelee;
//extern struct enemy;
struct enemy enemies[MAX_ENEMIES];
extern struct player player;
// for player and enemy attack collision
extern struct playerAttack playerAttack[100];
//extern struct enemyAttack;
extern struct enemyAttack bullet;
extern float dt;

void InitializeObstacle(int index) {
    float xRange, yRange;
    float dx, dy, distance, bufferDistance;
    bool overlap;
    do {
        xRange = CP_Random_RangeFloat(150, 1300);
        yRange = CP_Random_RangeFloat(150, 700);
        dx = player.position.x - xRange;
        dy = player.position.y - yRange;
        distance = (float)sqrt(dx * dx + dy * dy);
        bufferDistance = player.diameter + 100;
        overlap = distance < bufferDistance; // Check if the obstacle is too close to the player
		// for enemy overlap
        for (int i = 0; i < MAX_ENEMIES && !overlap; i++) {
            if (enemies[i].active) {
                dx = enemies[i].position.x - xRange;
                dy = enemies[i].position.y - yRange;
                distance = (float)sqrt(dx * dx + dy * dy);
                bufferDistance = enemies[i].diameter + 100;
                if (distance < bufferDistance) {
                    overlap = true; // Set overlap to true if too close to any enemy
                }
            }
        }
    } while (overlap); // Regenerate if too close
    obstacle[index].x = xRange;
    obstacle[index].y = yRange;
    // Debugging information
    printf("Obstacle %d initialized at (%f, %f)\n", index, xRange, yRange);
}

// checks for collision
bool CheckCollision(CP_Vector player_position, float playerDiameter, CP_Vector obstacle, float obstacleSize) {
	// calculate the player's position with the radius
    float playerRadius = playerDiameter / 2.0f;
    float playerLeft = player_position.x - playerRadius;
    float playerRight = player_position.x + playerRadius;
    float playerTop = player_position.y - playerRadius;
    float playerBottom = player_position.y + playerRadius;
	// calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
	// check if the player is colliding with the obstacle
    return playerRight > obstacleLeft && playerLeft < obstacleRight &&
        playerBottom > obstacleTop && playerTop < obstacleBottom;
}

// handles the collision
void HandleCollision(CP_Vector* player_position, float playerDiameter, CP_Vector obstacle, float obstacleSize) {
	// calculate the player's position with the radius
    float playerRadius = playerDiameter / 2.0f;
    float playerLeft = player_position->x - playerRadius;
    float playerRight = player_position->x + playerRadius;
    float playerTop = player_position->y - playerRadius;
    float playerBottom = player_position->y + playerRadius;
	// calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
	// calculate the overlap of the player and the obstacle
    float overlapLeft = playerRight - obstacleLeft;
    float overlapRight = obstacleRight - playerLeft;
    float overlapTop = playerBottom - obstacleTop;
    float overlapBottom = obstacleBottom - playerTop;
	// check the direction of the overlap
    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;
	// calculate the minimum overlap
    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;
	// move the player back based on the minimum overlap
    if (minOverlapX < minOverlapY) {
        player_position->x += fromLeft ? -minOverlapX : minOverlapX;
    }
    else {
        player_position->y += fromTop ? -minOverlapY : minOverlapY;
    }
}

// checks for enemy collision
bool CheckEnemyCollision(CP_Vector enemy_position, float enemyDiameter, CP_Vector obstacle, float obstacleSize) {
    // calculate the enemy's position with the radius
    float enemyRadius = enemyDiameter / 2.0f;
    float enemyLeft = enemy_position.x - enemyRadius;
    float enemyRight = enemy_position.x + enemyRadius;
    float enemyTop = enemy_position.y - enemyRadius;
    float enemyBottom = enemy_position.y + enemyRadius;
    // calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
    // check if the enemy is colliding with the obstacle
    return enemyRight > obstacleLeft && enemyLeft < obstacleRight &&
        enemyBottom > obstacleTop && enemyTop < obstacleBottom;
}

// handles the enemy collision
void HandleEnemyCollision(CP_Vector* enemy_position, float enemyDiameter, CP_Vector obstacle, float obstacleSize) {
    // calculate the enemy's position with the radius
    float enemyRadius = enemyDiameter / 2.0f;
    float enemyLeft = enemy_position->x - enemyRadius;
    float enemyRight = enemy_position->x + enemyRadius;
    float enemyTop = enemy_position->y - enemyRadius;
    float enemyBottom = enemy_position->y + enemyRadius;
    // calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
    // calculate the overlap of the enemy and the obstacle
    float overlapLeft = enemyRight - obstacleLeft;
    float overlapRight = obstacleRight - enemyLeft;
    float overlapTop = enemyBottom - obstacleTop;
    float overlapBottom = obstacleBottom - enemyTop;
    // check the direction of the overlap
    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;
    // calculate the minimum overlap
    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;
    // move the enemy back based on the minimum overlap
    if (minOverlapX < minOverlapY) {
        enemy_position->x += fromLeft ? -minOverlapX : minOverlapX;
    }
    else {
        enemy_position->y += fromTop ? -minOverlapY : minOverlapY;
    }
}

// checks for projectile collision
bool CheckBulletCollision(CP_Vector bullet_position, float bulletDiameter, CP_Vector obstacle, float obstacleSize) {
    // calculate the bullet's position with the radius
    float bulletRadius = bulletDiameter / 2.0f;
    float bulletLeft = bullet_position.x - bulletRadius;
    float bulletRight = bullet_position.x + bulletRadius;
    float bulletTop = bullet_position.y - bulletRadius;
    float bulletBottom = bullet_position.y + bulletRadius;
    // calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
    // check if the bullet is colliding with the obstacle
    return bulletRight > obstacleLeft && bulletLeft < obstacleRight &&
        bulletBottom > obstacleTop && bulletTop < obstacleBottom;
}

void HandleProjectileCollision(struct enemyAttack* bullet) {
    bullet->active = 0;
}

bool CheckPlayerBulletCollision(CP_Vector playerBullet_position, float playerBulletDiameter, CP_Vector obstacle, float obstacleSize) {
    // calculate the bullet's position with the radius
    float playerBulletRadius = playerBulletDiameter / 2.0f;
    float playerBulletLeft = playerBullet_position.x - playerBulletRadius;
    float playerBulletRight = playerBullet_position.x + playerBulletRadius;
    float playerBulletTop = playerBullet_position.y - playerBulletRadius;
    float playerBulletBottom = playerBullet_position.y + playerBulletRadius;
    // calculate the obstacle's position and its radius
    float obstacleLeft = obstacle.x;
    float obstacleRight = obstacle.x + obstacleSize;
    float obstacleTop = obstacle.y;
    float obstacleBottom = obstacle.y + obstacleSize;
    // check if the bullet is colliding with the obstacle
    return playerBulletRight > obstacleLeft && playerBulletLeft < obstacleRight &&
           playerBulletBottom > obstacleTop && playerBulletTop < obstacleBottom;
}

void HandlePlayerProjectileCollision(struct playerAttack* bullet) {
    playerAttack->isActive = 0;
}


void UpdateObstacles(int roomsPassed, CP_Vector player_position, float playerDiameter) {
    // Update the number of obstacles based on the number of rooms
    // Check if the player has entered a new room
    if (lastRoom != roomsPassed) {
        int newObstacleCount = CP_Random_RangeInt(3, 10); // Randomly generate the number of obstacles within the range 3 to 10
        for (int i = currentObstacleCount; i < newObstacleCount; i++) { // Initialize new obstacles if the count has increased
            InitializeObstacle(i);
        }
        currentObstacleCount = newObstacleCount;
        lastRoom = roomsPassed; // Update the last room to the current room
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active == 1 && enemies[i].type == 2) { // melee enemy
            for (int j = 0; j < currentObstacleCount; j++) {
                if (CheckEnemyCollision(enemies[i].position, enemies[i].diameter, obstacle[j], obstacle_diameter)) {
                    HandleEnemyCollision(&enemies[i].position, enemies[i].diameter, obstacle[j], obstacle_diameter);
                }
            }
        }
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active == 1 && enemies[i].type == 1) { // stationary enemy
            for (int j = 0; j < currentObstacleCount; j++) {
                if (CheckEnemyCollision(enemies[i].position, enemies[i].diameter, obstacle[j], obstacle_diameter)) {
                    HandleEnemyCollision(&enemies[i].position, enemies[i].diameter, obstacle[j], obstacle_diameter);
                }
            }
        }
    }
    // Check for player bullet collisions with obstacles
    for (int i = 0; i < 2; i++) {
        if (playerAttack[i].isActive) {
            // Check for collision with obstacles
            for (int j = 0; j < currentObstacleCount; j++) {
                if (CheckPlayerBulletCollision(playerAttack[i].position, playerAttack[i].diameter, obstacle[j], obstacle_diameter)) {
                    HandlePlayerProjectileCollision(&playerAttack[i]);
                    break; // Exit the loop once a collision is detected
                }
            }
        }
    }
    // Drawing Obstacles
    for (int i = 0; i < currentObstacleCount; i++) {
        CP_Settings_Fill(CP_Color_Create(150, 255, 100, 255));
        CP_Graphics_DrawRect(obstacle[i].x, obstacle[i].y, obstacle_diameter, obstacle_diameter);
    }
}

