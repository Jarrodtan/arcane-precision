#include "cprocessing.h"
#include "mainmenu.h"
#include "stdlib.h"
#include "utils.h"
#include "itemDrop.h"
#include "game.h"
#include "enemy.h"
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_ITEMS 100

extern float dt;
extern int roomsPassed;



struct itemDrops item[MAX_ITEMS];


void initialize_itemDrop(struct itemDrops *item,CP_Vector position) {
	item->position = position;
	item->top.x = item->position.x;
	item->top.y = item->position.y - 20;
	item->left.x = item->position.x - 20;
	item->left.y = item->position.y + 10;
	item->right.x = item->position.x + 20;
	item->right.y = item->position.y + 10;
	item->active = 1;
	item->effect = CP_Random_RangeInt(0, 6); //change here when adding more effects CP_Random_RangeInt(0,6)
	item->radius = 30;
	switch (item->effect) // add on different color
	{
	case heal:
		item->effectColor = CP_Color_Create(0, 255, 0, 255);
		break;
	case dmg:
		item->effectColor = CP_Color_Create(255, 0, 0, 255);
		break;
	case movespeed:
		item->effectColor = CP_Color_Create(0, 0, 255, 255);
		break;
	case hitboxSizeUp:
		item->effectColor = CP_Color_Create(255, 255, 107, 255);
		break;
	case cooldownDown:
		item->effectColor = CP_Color_Create(0, 255, 255, 255);
		break;
	case manaBuildUp:
		item->effectColor = CP_Color_Create(90, 34, 139, 255);
		break;
	case attackSpdUp:
		item->effectColor = CP_Color_Create(249, 105, 14, 255);
		break;
	}
}



void update_item(struct itemDrops *item, struct player *player)
{
	for (int u = 0; u < MAX_ITEMS; u++)
	{
		if (item[u].active == 1)
		{
			CP_Settings_Fill(item[u].effectColor);
			CP_Graphics_DrawTriangle(item[u].top.x,item[u].top.y, item[u].left.x, item[u].left.y, item[u].right.x,item[u].right.y);
			
			//collision with player
			if (CP_Vector_Distance(player->position, item[u].position) <= (player->diameter / 2) + (item[u].radius / 2))
			{
				item[u].active = 0;
				switch (item[u].effect) //add on different effects on player
				{
				case heal:
					player->lives++;
					break;
				case dmg:
					player->attackDamage += 1;
					break;
				case movespeed:
					player->moveSpeed += 50;
					break;
				case cooldownDown:
					player->cooldownSpeed += 5.00f;
					break;
				case attackSpdUp:
					player->attackSpeed += 50.0f;
					break;
				case manaBuildUp:
					if (player->manaBuildSpeed <= 150.0f)
					{
					player->manaBuildSpeed += 5.00f;
					}
					break;
				case hitboxSizeUp:
					if (player->hitboxSize <= 2.0f)
					{
					player->hitboxSize += 0.2f;
					}
					break;
				}

			}
	
		}
	}
}


