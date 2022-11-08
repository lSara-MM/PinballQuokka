#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

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
	b2RevoluteJointDef* rDef;
	PhysBody* Pala1;
	PhysBody* Pala2;
	int pala1X = 20;
	int pala1Y = 20;
	SDL_Rect spring;
	int compresion=0;
	//Textures
	SDL_Texture* texture;
	
};