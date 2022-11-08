#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL/include/SDL.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect spring;
	int compresion=0;
	//Textures
	SDL_Texture* texture;
	
};