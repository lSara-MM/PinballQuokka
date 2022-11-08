#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

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
	App->renderer->Blit(texture, position.x, position.y, NULL, 1.0f);


	return UPDATE_CONTINUE;
}



