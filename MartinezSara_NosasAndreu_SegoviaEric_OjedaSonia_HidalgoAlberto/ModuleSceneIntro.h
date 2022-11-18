#pragma once
#include "Module.h"
#include "Globals.h"

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

	Uint32 startTime = 0;
	uint dTime;
};
