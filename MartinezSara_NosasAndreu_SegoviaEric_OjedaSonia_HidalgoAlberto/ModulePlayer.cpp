#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	//DATA DEL MUELLE
	springData.x = 700;
	springData.y = 200;
	springData.w = 25;
	springData.h = 10;

	//LANZADOR
	
	base = App->physics->CreateRectangleSensor(springData.x, springData.y, springData.w, springData.h /*, App->physics->STATIC*/);//Superficie apoyo

	//MUELLE EN SI
	spring = App->physics->CreateRectangle(springData.x, springData.y+springData.h, springData.w, springData.h, App->physics->DYNAMIC);
	
	App->physics->CreatePrismaticJoint(spring, VecS1, base, VecS2, axis, 2, false, true); //TODO: Modificar funcion para max y min

	//texture = App->textures->Load("pinball/muelle.png");


	//PALAS

	circle = App->physics->CreateCircle(600, 200, 2, App->physics->STATIC);

	rect = App->physics->CreateRectangle(600, 200, 64, 10, App->physics->DYNAMIC);

	App->physics->CreateRevoluteJoint(rect, Vec1, circle, Vec2, 33.0f);

	Vec1 = { -0.50, 0 };

	circle2 = App->physics->CreateCircle(400, 200, 2, App->physics->STATIC);

	rect2 = App->physics->CreateRectangle(464, 200, 64, 10, App->physics->DYNAMIC);

	App->physics->CreateRevoluteJoint(rect2, Vec1, circle2, Vec2, 33.0f);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	//Posicion muelle
	springData.x = spring->body->GetTransform().p.x;
	springData.y = spring->body->GetTransform().p.y;

	//App->renderer->Blit(texture, springData.x, springData.y, NULL, 1.0f);
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		spring->body->ApplyForce(b2Vec2(0, -30), b2Vec2(0, 0), true);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		spring->body->ApplyForce(b2Vec2(0, 30), b2Vec2(0, 0), true);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		rect2->body->ApplyForce(b2Vec2(-30, -30), b2Vec2(0, -5), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		rect->body->ApplyForce(b2Vec2(-30, -30), b2Vec2(0, -5), true);
	}


	return UPDATE_CONTINUE;
}



