#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "ModuleScene.h"
#include <iostream>
using namespace std;
#include <sstream>

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{
	
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	//DATA DEL MUELLE
	springData.x = 445;
	springData.y = 600;
	springData.w = 40;
	springData.h = 25;

	//LANZADOR
	
	base = App->physics->CreateRectangle(springData.x+ springData.w, springData.y+10, springData.w, 1, App->physics->STATIC, ColliderType::UNKNOWN);//Superficie apoyo

	//MUELLE EN SI
	spring = App->physics->CreateRectangle(springData.x+ springData.w, springData.y+springData.h, springData.w, springData.h, App->physics->DYNAMIC, ColliderType::UNKNOWN);
	jointMuelle = App->physics->CreatePrismaticJoint(spring, VecS1, base, VecS2, axis, -MaxLength/2, MaxLength, false, true); //TODO: Modificar funcion para max y min
	textureMuelle = App->textures->Load("pinball/muelle.png");


	//PALAS
	circle = App->physics->CreateCircle(300, 790, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect = App->physics->CreateRectangle(300, 790, 35, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	Vec1 = { 0.50, 0 };
	App->physics->CreateRevoluteJoint(rect, Vec1, circle, Vec2, 33.0f);
	Vec1 = { -0.50, 0 };

	circle2 = App->physics->CreateCircle(196, 790, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect2 = App->physics->CreateRectangle(196, 790, 35, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	//Fliper derecho
	fliperD.x = 300;
	fliperD.y = 790;
	circle = App->physics->CreateCircle(fliperD.x, fliperD.y, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect = App->physics->CreateRectangle(fliperD.x, fliperD.y, 50, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	Vec1 = /*{ 0.50, 0 }*/{ 0.50, 0 };
	App->physics->CreateRevoluteJoint(rect, Vec1, circle, Vec2, 30.0f);
	Vec1 = { -0.50, 0 };

	//Fliper Izquierdo
	fliperI.x = 196;
	fliperI.y = 790;
	circle2 = App->physics->CreateCircle(fliperI.x, fliperI.y, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect2 = App->physics->CreateRectangle(fliperI.x, fliperI.y, 50, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	App->physics->CreateRevoluteJoint(rect2, Vec1, circle2, Vec2, 30.0f);
	textureFlipers= App->textures->Load("pinball/fliper.png");

	numBalls = 3;
	// Score
	score = 0;
	comboPaws = 0;
	
	// Load Font
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   .,:!?()- " };
	scoreFont = App->renderer->LoadFont("Pinball/font_CatPaw32.png", lookupTable, 6, 13); // 6 = rows 
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	if (spring->body->GetFixtureList())
	{
		spring->body->DestroyFixture(spring->body->GetFixtureList());
	}
	if (base->body->GetFixtureList())
	{
		base->body->DestroyFixture(base->body->GetFixtureList());
	}
	if (rect->body->GetFixtureList())
	{
		rect->body->DestroyFixture(rect->body->GetFixtureList());
	}
	if (rect2->body->GetFixtureList())
	{
		rect2->body->DestroyFixture(rect2->body->GetFixtureList());
	}
	if (circle->body->GetFixtureList())
	{
		circle->body->DestroyFixture(circle->body->GetFixtureList());
	}
	if (circle2->body->GetFixtureList())
	{
		circle2->body->DestroyFixture(circle2->body->GetFixtureList());
	}
	

	//App->renderer->UnLoadFont(scoreFont);
	return true;	
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//MUELLE
	//Posicion muelle
	springData.x = METERS_TO_PIXELS(spring->body->GetTransform().p.x);
	springData.y = METERS_TO_PIXELS(spring->body->GetTransform().p.y);

	if (SpringReleased == true)
	{
		--timer;
		if (timer <= 0) {

			compresion = 0.1;
			SpringReleased = false;
			timer = 100;
		}
	}
	jointMuelle->SetLimits(-compresion / 4, compresion);


	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && compresion <= 8)
	{
		//setearlo
		SpringReleased = false;
		if (compresion == 0)
		{
			compresion = 0.1;
		}
		//comprimir el muelle
		compresion += (0.025 - compresion / 320);
		//LOG("%f", compresion);
		jointMuelle->SetLimits(compresion / 4, compresion);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP && compresion >= 0)
	{
		SpringReleased = true;
		spring->body->ApplyForce(b2Vec2(/*-MaxLength / 2*/ 0, -compresion * compresion * 25), b2Vec2(0, 0), true);
	}
	App->renderer->Blit(textureMuelle, springData.x - 25, springData.y - 15, NULL, 0.4F); //Al convertir de metros a pixeles hay cierto error de redondeo asi que ponemos el -25 y el -15

	//FLIPERS

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		rect2->body->ApplyForce(b2Vec2(-2, -2), b2Vec2(0, -5), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		rect->body->ApplyForce(b2Vec2(2, -2), b2Vec2(0, -5), true);
	}

	int x, y;
	rect->GetPosition(x, y);
	App->renderer->Blit(textureFlipers, x - 10, y, NULL, 0.3F, NULL, rect->GetRotation(), NULL, NULL, SDL_FLIP_HORIZONTAL);

	rect2->GetPosition(x, y);
	App->renderer->Blit(textureFlipers, x, y - 33, NULL, 0.3F, NULL, rect2->GetRotation(), NULL, NULL, SDL_FLIP_NONE);


	rect->GetPosition(x,y);
	App->renderer->Blit(textureFlipers, fliperD.x+50, fliperD.y-50, NULL, 0.3F, NULL, rect->GetRotation(), NULL, NULL, SDL_FLIP_HORIZONTAL);

	rect2->GetPosition(x, y);
	App->renderer->Blit(textureFlipers,fliperI.x-80, fliperI.y-20-(sin(rect2->GetRotation())*75), NULL, 0.3F, NULL, rect2->GetRotation(), NULL, NULL, SDL_FLIP_NONE); //Posicio neutral cuando angulo=0 (-80,-20)
	

	// strings to const char*
	string s_score = std::to_string(score);
	const char* ch_score = s_score.c_str();
	App->renderer->BlitText(120, 15, scoreFont, "Score:");
	App->renderer->BlitText(300, 15, scoreFont, ch_score);

	return UPDATE_CONTINUE;
}

