#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

#include "Animation.h"

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
	void loseLife();
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

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	float frames = 60.0f;

private:
	// Textures
	SDL_Texture* ball;
	SDL_Texture* fondo;
	SDL_Texture* map;

	SDL_Texture* texLoseCat;
	int subtitleFont;

	// FX
	uint bonus_fx;
	int audiohit;
	int audioimpact;
	int audiomiau; 
	int audiolose; 
	bool lose;


	// Combo
	bool greenP, purpleP, turquoiseP, pinkP;

	// Bounce valor
	float bounce = 0.6f;

	//God mode
	bool godMode;

	bool grav = false;
	bool fps = false;
	bool boing = false;
	bool lifeLose;
	bool retry;
	

	SDL_Rect bRetry;
	SDL_Rect bGoRanks;

	PhysBody* b1;
	PhysBody* b2;
	PhysBody* b3;
	PhysBody* b4;
	PhysBody* b5;
	PhysBody* b6;
	PhysBody* b7;
	PhysBody* b8;
	PhysBody* b9;
	PhysBody* b10;


	PhysBody* backGround;
	PhysBody* b11;
	PhysBody* b12;
	PhysBody* sensor_1;
	PhysBody* sensor_2;
	PhysBody* bola;
	

	PhysBody* Pink_Paw;
	PhysBody* Turqupise_Paw;
	PhysBody* Green_Paw;
	PhysBody* Purple_Paw;

};
