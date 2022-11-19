#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

class ModuleLeaderboard : public Module
{
public:

	// Constructors & Destructors
	ModuleLeaderboard(Application* app, bool start_enabled = true);
	~ModuleLeaderboard();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();

	void ranks();
	void bubbleSort(int array[], int size);
public:

	
	// Textures
	SDL_Texture* bgTexture;

	Animation animLurkingCat;
	SDL_Texture* texLurkingCat;

	// FX
	//uint bonus_fx;

	int leaderboard[10];
	int currentScore;
private:
	int titleFont;
	int subtitleFont;

	// Ranks
	Uint32 startTime = 0;
	uint dTime;
	int randNum;
	
	int prevScore[2];

	SDL_Rect bgColor;
};
