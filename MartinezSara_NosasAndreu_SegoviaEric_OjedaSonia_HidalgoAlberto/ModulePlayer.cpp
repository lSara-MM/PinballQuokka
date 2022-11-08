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
	springData.x = PIXEL_TO_METERS(200);
	springData.y = PIXEL_TO_METERS(200);
	springData.w = PIXEL_TO_METERS(50);
	springData.h = PIXEL_TO_METERS(100);

	//SUPERFICIE ESTATICA A LA QUE ESTA SUJETO EL MUELLE
	base = App->physics->CreateRectangle(30, 30, springData.w, springData.h, App->physics->STATIC);

	//MUELLE EN SI
	spring = App->physics->CreateRectangle(springData.x, springData.y, springData.w, springData.h, App->physics->DYNAMIC);
	
	texture = App->textures->Load("pinball/muelle.png");

	//PALAS

	Pala1 = App->physics->CreateRectangle(pala1X + 600, pala1Y + 20, 200, 100, App->physics->KINEMATIK);
	Pala2 = App->physics->CreateRectangle(pala1X + 600, pala1Y + 150, 200, 100, App->physics->KINEMATIK);

	rDef = new b2RevoluteJointDef;
	rDef->bodyA = Pala1->body;
	rDef->bodyB = Pala2->body;
	rDef->collideConnected = false;
	rDef->localAnchorA.Set(0, 0);	
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

	//Posicion muelle
	springData.x = spring->body->GetTransform().p.x;
	springData.y = spring->body->GetTransform().p.y;

	App->renderer->Blit(texture, springData.x, springData.y, NULL, 1.0f);
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		compresion -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN){
		Pala1->body->SetType(b2BodyType::b2_dynamicBody);
		Pala2->body->SetType(b2BodyType::b2_dynamicBody);
	}


	return UPDATE_CONTINUE;
}



