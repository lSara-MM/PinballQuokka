#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL/include/SDL.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	iPoint position;
	SDL_Rect spring;
	//Textures
	SDL_Texture* texture;
	
};