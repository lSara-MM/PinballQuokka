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
	spring.x = METERS_TO_PIXELS(100);
	spring.y = METERS_TO_PIXELS(100);
	spring.w = METERS_TO_PIXELS(0, 5);
	spring.h = METERS_TO_PIXELS(1);
	App->physics->CreateRectangle(spring.x, spring.y, spring.w, spring.h, App->physics->KINEMATIK);
	texture = App->textures->Load("pinball/muelle.png");

	//PALAS

	Pala1 = App->physics->CreateRectangle(pala1X, pala1Y, 200, 100, App->physics->KINEMATIK);
	Pala2 = App->physics->CreateRectangle(pala1X + 20, pala1Y + 20, 200, 100, App->physics->KINEMATIK);

	rDef = new b2RevoluteJointDef;
	rDef->bodyA = Pala1->body;
	rDef->bodyB = Pala2->body;
	App->physics->world->CreateJoint(rDef);

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
	App->renderer->Blit(texture, spring.x, spring.y, &spring, 1.0f);
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		compresion -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN){}


	return UPDATE_CONTINUE;
}



