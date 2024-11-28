//---------------------------------------------------------
// file:	main.c
// author:	[Toh Jing Han]
// email:	[jinghan.toh@digipen.edu]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// Copyright ? 2024 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "splashscreen.h"


int main(void)
{
	CP_Engine_SetNextGameState(splashscreen_Init, splashscreen_Update,splashscreen_Exit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run(0);
	return 0;
}
