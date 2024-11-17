#pragma once
#include "cprocessing.h"

enum effects { //expand this when needed
	heal = 0,
	dmg = 1, 
	movespeed = 2,
	cooldownDown = 3,
	attackSpdUp = 4,
	manaBuildUp = 5,
	attackSizeUp = 6
};

struct itemDrops {
	CP_Vector position;
	CP_Vector top; //top vertex of triangle
	CP_Vector left; //left vertex of triangle
	CP_Vector right; //right vertex of triangle
	float radius; // radius for hitbox (no visual effects)
	enum effects effect;
	CP_Color effectColor;
	int active;
};

void initialize_itemDrop(struct itemDrops* item,CP_Vector position);
void update_item(struct itemDrops *item, struct player *player);
