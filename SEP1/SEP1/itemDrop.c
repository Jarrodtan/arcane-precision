//---------------------------------------------------------
// file:	itemDrop.c
// author:	[Toh Jing Han]
// email:	[jinghan.toh@digipen.edu]
//
// brief:	itemDrop.c holds the functions for handling initializing of item ddrops, updating and collision handling
//
// Copyright © 2024 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "utils.h"
#include "itemDrop.h"
#include "game.h"
#include "enemy.h"

#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_ITEMS 100


struct itemDrops item[MAX_ITEMS];

//initializes items dropped when enemy dies.
void initialize_itemDrop(struct itemDrops *item,CP_Vector position) {
	item->position = position;
	item->top.x = item->position.x;
	item->top.y = item->position.y - 20;
	item->left.x = item->position.x - 20;
	item->left.y = item->position.y + 10;
	item->right.x = item->position.x + 20;
	item->right.y = item->position.y + 10;
	item->active = 1;
	item->effect = CP_Random_RangeInt(0, 6); //randomizes effects when initialize
	item->radius = 30;
	switch (item->effect) // add on different color according to which effect the item does
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


//update drawing of item
void update_item(struct itemDrops *item, struct player *player)
{
	for (int u = 0; u < MAX_ITEMS; u++)
	{
		if (item[u].active == 1) //checking if item in array is active
		{
			CP_Settings_Fill(item[u].effectColor);
			CP_Graphics_DrawTriangle(item[u].top.x,item[u].top.y, item[u].left.x, item[u].left.y, item[u].right.x,item[u].right.y);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Settings_TextSize(20.0f);
			switch (item[u].effect)// draw text below item accordingly to effect
			{
			case heal:
			CP_Font_DrawText("Heal 1 Heart", item[u].position.x - 48, item[u].position.y + 30);
				break;
			case dmg:
				CP_Font_DrawText("Fire DMG Up", item[u].position.x - 58, item[u].position.y + 30);
				break;
			case movespeed:
				CP_Font_DrawText("Move Speed Up", item[u].position.x - 62, item[u].position.y + 30);
				break;
			case cooldownDown:
				CP_Font_DrawText("Cooldown Speed Up", item[u].position.x - 80, item[u].position.y + 30);
				break;
			case attackSpdUp:
				CP_Font_DrawText("Attack Speed Up", item[u].position.x - 66, item[u].position.y + 30);
				break;
			case manaBuildUp:
				CP_Font_DrawText("Mana Build Speed Up", item[u].position.x - 86, item[u].position.y + 30);
				break;
			case hitboxSizeUp:
				CP_Font_DrawText("Hitbox Size Up", item[u].position.x - 58, item[u].position.y + 30);
				break;
			}
			
			//collision with player
			if (CP_Vector_Distance(player->position, item[u].position) <= (player->diameter / 2) + (item[u].radius / 2))
			{
				item[u].active = 0;
				switch (item[u].effect) //add on different effects on player depending on effects
				{
				case heal:
					player->lives++;
					break;
				case dmg:
					player->attackDamage += 1;
					break;
				case movespeed:
					if (player->moveSpeed <= 1000) // setting limit for balance
					{
						player->moveSpeed += 50;
					}
					break;
				case cooldownDown:
					player->cooldownSpeed += 5.00f;
					break;
				case attackSpdUp:
					player->attackSpeed += 50.0f;
					break;
				case manaBuildUp:
					if (player->manaBuildSpeed <= 150.0f) // setting limit for balance
					{
						player->manaBuildSpeed += 5.00f;
					}
					break;
				case hitboxSizeUp:
					if (player->hitboxSize <= 2.0f) // setting limit for balance
					{
						player->hitboxSize += 0.2f;
					}
					break;
				}
			}
		}
	}
}
