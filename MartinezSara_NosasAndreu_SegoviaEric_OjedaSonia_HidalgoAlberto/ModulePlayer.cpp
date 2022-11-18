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
	springData.x = 445;
	springData.y = 600;
	springData.w = 40;
	springData.h = 25;

	//LANZADOR
	
	base = App->physics->CreateRectangle(springData.x+ springData.w, springData.y+10, springData.w, 1, App->physics->STATIC, ColliderType::UNKNOWN);//Superficie apoyo

	//MUELLE EN SI
	spring = App->physics->CreateRectangle(springData.x+ springData.w, springData.y+springData.h, springData.w, springData.h, App->physics->DYNAMIC, ColliderType::UNKNOWN);
	jointMuelle = App->physics->CreatePrismaticJoint(spring, VecS1, base, VecS2, axis, -MaxLength/2, MaxLength, false, true); //TODO: Modificar funcion para max y min
	texture = App->textures->Load("pinball/muelle1.png");


	//PALAS

	circle = App->physics->CreateCircle(600, 200, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect = App->physics->CreateRectangle(600, 200, 64, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	App->physics->CreateRevoluteJoint(rect, Vec1, circle, Vec2, 33.0f);
	Vec1 = { -0.50, 0 };

	circle2 = App->physics->CreateCircle(400, 200, 2, App->physics->STATIC, ColliderType::UNKNOWN);
	rect2 = App->physics->CreateRectangle(464, 200, 64, 10, App->physics->DYNAMIC, ColliderType::UNKNOWN);

	App->physics->CreateRevoluteJoint(rect2, Vec1, circle2, Vec2, 33.0f);


	// Score
	score = 0;

	// Load Font
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:!?()-" };
	scoreFont = App->renderer->LoadFont("Pinball/font_CatPaw.png", lookupTable, 6, 13); // 6 = rows 
	
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

	if (spring->body->GetAngularVelocity() == 0 && SpringReleased == true)
	{
		compresion = 0.1;
		SpringReleased = false;
	}
	jointMuelle->SetLimits(-0.01, compresion);

	//App->renderer->Blit(texture, springData.x, springData.y, NULL, 1.0f);
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && compresion<=4)
	{
		if (compresion == 0)
		{
			compresion = 0.05;
		}

		compresion += (0.05-compresion/85);
		LOG("%f",compresion)
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP )
	{
		SpringReleased = true;
		spring->body->ApplyForce(b2Vec2(-MaxLength / 2, -compresion * compresion*85), b2Vec2(0, 0), true);
		
	}

	App->renderer->Blit(texture, (float)METERS_TO_PIXELS(springData.x), (float)METERS_TO_PIXELS(springData.y));

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		rect2->body->ApplyForce(b2Vec2(-30, -30), b2Vec2(0, -5), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		rect->body->ApplyForce(b2Vec2(-30, -30), b2Vec2(0, -5), true);
	}

	App->renderer->BlitText(80, 20, scoreFont, "score", 0.65f);
	return UPDATE_CONTINUE;
}



