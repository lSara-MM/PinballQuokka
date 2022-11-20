#pragma once
#include "Module.h"
#include "Globals.h"

#include "Animation.h"

class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();

public:

private:
	int titleFont;
	int subtitleFont;

	SDL_Texture* bgTexture;
	Animation animPlayCat;
	SDL_Texture* texPlayCat;


	Uint32 startTime = 0;
	uint dTime;
};
