#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

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
	//Palas
	b2RevoluteJointDef* rDef;
	PhysBody* Pala1;
	PhysBody* Pala2;
	int pala1X = 20;
	int pala1Y = 20;

	//Muelle lanzador
	SDL_Rect springData;
	int compresion=0;
	PhysBody* spring;
	PhysBody* base;
	//Textures
	SDL_Texture* texture;
	
};