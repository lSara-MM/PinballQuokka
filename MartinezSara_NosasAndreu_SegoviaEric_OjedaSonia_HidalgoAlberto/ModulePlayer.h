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
	PhysBody* rect;
	PhysBody* rect2;
	PhysBody* circle;
	PhysBody* circle2;

	b2Vec2 Vec1 = b2Vec2(0.50, 0);
	b2Vec2 Vec2 = b2Vec2(0, 0);

	//Muelle lanzador
	SDL_Rect springData;
	float compresion=0.1;
	float MaxLength=4;
	bool SpringReleased= false;
	short timer=100;
	PhysBody* spring;
	PhysBody* base;
	b2PrismaticJoint* jointMuelle;

	b2Vec2 VecS1 = b2Vec2(0, 0);
	b2Vec2 VecS2 = b2Vec2(0, 0);
	b2Vec2 axis = b2Vec2(0, -1);

	// Balls
	int numBalls; 

	//Textures
	SDL_Texture* texture;

	int scoreFont;
	int score;
	int comboPaws;
};