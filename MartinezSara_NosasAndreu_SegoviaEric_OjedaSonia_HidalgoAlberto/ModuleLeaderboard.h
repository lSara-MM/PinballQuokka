#pragma once
#include "Module.h"
#include "Globals.h"

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
	//SDL_Texture* map;

	// FX
	//uint bonus_fx;

private:
	int titleFont;
	int subtitleFont;

	Uint32 startTime = 0;
	uint dTime;

	// Ranks
	int leaderboard[10];
	int prevScore;
};
