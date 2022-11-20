#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleScene : public Module
{
public:

	// Constructors & Destructors
	ModuleScene(Application* app, bool start_enabled = false);
	~ModuleScene();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	bool loseGame();

	void debug();
public:

	// Lists of physics objects
	p2List<PhysBody*> circles;
	p2List<PhysBody*> slingershots;
	p2List<PhysBody*> chains;
	

	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	bool sensed;

	// Textures
	SDL_Texture* ball;
	SDL_Texture* fondo; 
	SDL_Texture* map;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	// Combo
	bool greenP, purpleP, turquoiseP, pinkP;

	// Bounce valor

	float bounce = 1.2f;

	bool grav = false;
	float frames = 60.0f;
	bool fps = false;
	bool boing = false;
	bool normGrav = 0;
	bool lifeLose;

	bool pause;

	//Audio

	int audiohit; 

	PhysBody* b1;
	PhysBody* b2;
	PhysBody* b3;
	PhysBody* b4;
	PhysBody* b5;
	PhysBody* b6;
	PhysBody* b7;
	PhysBody* b8;
	PhysBody* b9;

	PhysBody* Pink_Paw;
	PhysBody* Turqupise_Paw;
	PhysBody* Green_Paw;
	PhysBody* Purple_Paw;
};
