#include "cprocessing.h"
#include "startmenu.h"
#include "utils.h"
#include "stdio.h"
#include "string.h"
#include "game.h"


#define WINDOW_WIDTH 1600.0f
#define WINDOW_HEIGHT 900.0f
#define MAX_NAME_LENGTH 10
#define MAX_LEADERBOARD 10

CP_Image gameover_sign;
extern CP_Font myFont;	
float textSize;
char playerName[MAX_NAME_LENGTH];// Array to hold the player's name
int cursorPosition; // Position of the cursor in the input string
extern struct player player;
char highscore[256];
extern const char* leaderboardSave;
leaderboard ldrboard[MAX_LEADERBOARD];
int count;

void gameover_Init(void)
{
	playerName[0] = '\0'; // Set the first character to null terminator
	sprintf_s(highscore, sizeof(highscore), "score: %d", player.score);
	cursorPosition = 0;
	gameover_sign = CP_Image_Load("Assets/gameoverscreen.png");
	CP_Settings_RectMode(CP_POSITION_CORNER);
	textSize = 50.0f;
	CP_Settings_TextSize(textSize);
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

	count = loadLeaderboard(ldrboard, "leaderboard.dat");
}
void gameover_Update(void)
{
	//highscore[1] = player.score;
	// Testing Gameover sign
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	CP_Image_Draw(gameover_sign, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.7f, 700.0f, 400.0f, 255);
	
	// Score: ______ (generated)
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(highscore, WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 1.55f);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 2.08f, WINDOW_HEIGHT / 1.5f, WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 15.0f);

	// Name: ______ (player input)
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("Name: ", WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 1.40f);
	
	// Draw the text box
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 2.08f, WINDOW_HEIGHT / 1.5f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 15.0f);

	// Draw the player's name inside the text box
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	// Adjust the y-position to be centered within the text box
	float textYPosition = (WINDOW_HEIGHT / 1.5f) + (WINDOW_HEIGHT / 10.0f) / 2.0f;
	CP_Font_DrawText(playerName, WINDOW_WIDTH / 2.04f, textYPosition);

	// Check for key presses
	if (CP_Input_KeyTriggered(KEY_BACKSPACE) && cursorPosition > 0) {
		cursorPosition--;
		playerName[cursorPosition] = '\0'; // Remove last character
	}
	else if (CP_Input_KeyTriggered(KEY_ENTER)) {
		if (cursorPosition > 0) { // Check if the name is not empty
			// Handle submission (e.g., save the name or proceed)
			// Optionally, transition to another game state
			switch (cursorPosition)
			{
			case 0:
				updateLeaderboard(ldrboard, &count, "ANON", player.score, leaderboardSave);
				break;
			default:
				updateLeaderboard(ldrboard, &count, playerName, player.score, leaderboardSave);
				break;
			}
			CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
		}
	}
	else {
		for (int i = 32; i < 127; i++) { // Only allow printable ASCII characters
			if (CP_Input_KeyTriggered(i) && cursorPosition < MAX_NAME_LENGTH - 1) {
				playerName[cursorPosition] = (char)i; // Store the character
				cursorPosition++;
				playerName[cursorPosition] = '\0'; // Null-terminate the string
				break;
			}
		}
	}


	//Back button
	CP_Settings_Fill(CP_Color_Create(255, 100, 0, 255));
	CP_Graphics_DrawRect(WINDOW_WIDTH / 2.4f, WINDOW_HEIGHT / 1.26f, WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f);
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Back", WINDOW_WIDTH / 2.13f, WINDOW_HEIGHT / 1.18f);
	if (IsAreaClicked(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.2f,
		WINDOW_WIDTH / 6.0f, WINDOW_HEIGHT / 12.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		switch (cursorPosition)
		{
		case 0:
			updateLeaderboard(ldrboard, &count, "ANON", player.score, leaderboardSave);
			break;
		default: 
			updateLeaderboard(ldrboard, &count, playerName, player.score, leaderboardSave);
			break;
		}
		CP_Engine_SetNextGameState(Start_Menu_Init, Start_Menu_Update, Start_Menu_Exit);
	}
}

void gameover_Exit(void)
{
	gameover_sign = CP_Image_Free;
}
