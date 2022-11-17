#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleScene::~ModuleScene()
{
	// You should do some memory cleaning here, if required
}

bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map = App->textures->Load("pinball/muelle.png");

	fondo = App->textures->Load("pinball/Fondo.png");
	int Fondo[168] = {
			175, 950,
			172, 820,
		   170, 818,
		   165, 811,
		   157, 807,
		   148, 803,
		   137, 799,
		   125, 795,
		   117, 793,
		   107, 789,
		   96, 784,
		   88, 780,
		   76, 775,
		   65, 771,
		   58, 766,
		   50, 761,
		   42, 753,
		   38, 749,
		   35, 742,
		   33, 736,
		   32, 728,
		   32, 717,
		   32, 67,
		   33, 64,
		   36, 58,
		   40, 52,
		   44, 46,
		   47, 41,
		   52, 35,
		   57, 31,
		   62, 27,
		   68, 23,
		   74, 18,
		   79, 15,
		   86, 12,
		   91, 10,
		   98, 6,
		   103, 4,
		   108, 3,
		   116, 2,
		   120, 2,
		   127, 1,
		   428, 0,
		   436, 4,
		   448, 10,
		   455, 14,
		   473, 30,
		   476, 34,
		   483, 41,
		   486, 46,
		   492, 54,
		   503, 70,
		   504, 818,
		   467, 818,
		   467, 206,
		   464, 202,
		   462, 201,
		   459, 201,
		   457, 203,
		   455, 206,
		   455, 208,
		   455, 727,
		   454, 733,
		   452, 741,
		   448, 749,
		   437, 764,
		   430, 768,
		   425, 771,
		   420, 773,
		   414, 775,
		   409, 778,
		   402, 780,
		   391, 784,
		   380, 789,
		   375, 790,
		   370, 792,
		   364, 794,
		   353, 798,
		   349, 800,
		   333, 807,
		   322, 812,
		   317, 818,
		   315, 820,
		   312, 950
	};

	int FondoOreja[40] = {
	67, 203,
	66, 303,
	69, 313,
	74, 321,
	82, 325,
	94, 325,
	105, 320,
	113, 312,
	116, 301,
	118, 271,
	128, 252,
	145, 241,
	150, 236,
	152, 225,
	130, 203,
	115, 192,
	97, 184,
	85, 182,
	78, 185,
	71, 193
	};

	int FondoOreja2[42] = {
	420, 209,
	420, 301,
	418, 314,
	411, 323,
	402, 326,
	389, 325,
	380, 319,
	372, 310,
	370, 303,
	369, 274,
	364, 262,
	358, 252,
	348, 245,
	338, 239,
	335, 232,
	336, 224,
	349, 210,
	374, 190,
	392, 184,
	407, 185,
	417, 197
	};

	int FondoBarra[10] = {
		80, 522,
		80, 647,
		88, 647,
		88, 523,
		84, 519
	};

	int FondoBarra2[10] = {
	404, 523,
	404, 648,
	413, 649,
	413, 523,
	409, 519
	};

	int FondoTriangle[22] = {
	93, 649,
	186, 728,
	188, 733,
	188, 741,
	184, 747,
	177, 752,
	77, 728,
	71, 720,
	71, 657,
	75, 651,
	83, 649
	};

	int FondoTriangle2[20] = {
	399, 648,
	304, 726,
	300, 733,
	302, 741,
	309, 747,
	315, 748,
	413, 728,
	420, 720,
	419, 654,
	407, 649
	};

	int FondoOval[40] = {
	177, 250,
	181, 254,
	183, 263,
	185, 276,
	186, 287,
	186, 300,
	186, 313,
	185, 332,
	183, 349,
	181, 357,
	177, 363,
	173, 357,
	170, 348,
	168, 331,
	168, 312,
	167, 299,
	168, 286,
	169, 275,
	171, 262,
	173, 254
	};

	int FondoOval2[40] = {
	247, 250,
	251, 254,
	253, 263,
	255, 276,
	256, 287,
	256, 300,
	256, 313,
	255, 332,
	253, 349,
	251, 357,
	247, 363,
	243, 357,
	240, 348,
	238, 331,
	238, 312,
	237, 299,
	238, 286,
	239, 275,
	241, 262,
	243, 254
	};

	int FondoOval3[40] = {
    314, 250,
    318, 254,
    320, 263,
    322, 276,
    323, 287,
	323, 300,
	323, 313,
	322, 332,
	320, 349,
	318, 357,
    314, 363,
    310, 357,
    307, 348,
    305, 331,
	305, 312,
	304, 299,
	305, 286,
	306, 275,
    308, 262,
	310, 254
	};


	

	App->physics->CreateChain(0, 0, Fondo, 168, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoOreja, 40, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoOreja2, 42, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoBarra, 10, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoBarra2, 10, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoTriangle, 22, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoTriangle2, 20, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoOval, 40, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoOval2, 40, App->physics->STATIC, ColliderType::UNKNOWN);
	App->physics->CreateChain(0, 0, FondoOval3, 40, App->physics->STATIC, ColliderType::UNKNOWN);

	PhysBody* circle1 = App->physics->CreateCircle(247, 64, 43, App->physics->STATIC); 
	PhysBody* circle2 = App->physics->CreateCircle(153, 134, 43, App->physics->STATIC); 
	PhysBody* circle3 = App->physics->CreateCircle(336, 134, 43, App->physics->STATIC); 
	PhysBody* circle4 = App->physics->CreateCircle(87, 483, 24, App->physics->STATIC); 
	PhysBody* circle5 = App->physics->CreateCircle(402, 483, 24, App->physics->STATIC); 

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	// Add this module (ModuleScene) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleScene::OnCollision()
	lower_ground_sensor->listener = this;
	
	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleScene::Update()
{
	//Dibujar el mapa
	App->renderer->Blit(fondo, 0, 0);
	App->renderer->Blit(map,0,0);

	// If user presses SPACE, enable RayCast
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// Enable raycast mode
		ray_on = !ray_on;

		// Origin point of the raycast is be the mouse current position now (will not change)
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	// If user presses 1, create a new circle object
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));

		// Add this module (ModuleScene) as a "listener" interested in collisions with circles.
		// If Box2D detects a collision with this last generated circle, it will automatically callback the function ModulePhysics::BeginContact()
		circles.getLast()->data->listener = this;
	}

	// If user presses 2, create a new box object
	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	// If user presses 3, create a new RickHead object
	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};
		
		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64, App->physics->DYNAMIC,ColliderType::UNKNOWN));
	}

	//Slingershot
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

		int triangle[6] = {
				0, 0,
				400, 0,
				200, 200,//valors arbirtaris, canviar en funció mapa

		};

		slingershots.add(App->physics->CreateBouncyChain(App->input->GetMouseX(), App->input->GetMouseY(), triangle, 6, 2, App->physics->STATIC, ColliderType::UNKNOWN));
	}


	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{


		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_intro, 90);
	}

	

	// Prepare for raycast ------------------------------------------------------
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	// Circles
	p2List_item<PhysBody*>* c = circles.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// If mouse is over this circle, paint the circle's texture
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());

		c = c->next;
	}

	// Boxes
	c = boxes.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// Always paint boxes texture
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());

		// Are we hitting this box with the raycast?
		if(ray_on)
		{
			// Test raycast over the box, return fraction and normal vector
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	// Rick Heads
	c = ricks.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	//Slingershots
	c = slingershots.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		//App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	App->audio->PlayFx(bonus_fx);

	/*
	switch (bodyB->ctype)
	{
		case ColliderType::PLATFORM:
			LOG("Collider platform");
			//WHATEVER

			break;

		case ColliderType::EYES:
			LOG("Collider eyes");
			//WHATEVER
		
			break;

		case ColliderType::ORANGE_BUMPER:
			LOG("Collider bumper paw");
			//WHATEVER
			break;

		case ColliderType::SLINGERSHOT:
			LOG("Collider slingershot paw");
			//WHATEVER
			break;

		case ColliderType::GREEN_PAW:
			LOG("Collider green paw");
			//WHATEVER
			break;
		
		case ColliderType::PURPLE_PAW:
			LOG("Collider purple paw");
			//WHATEVER
			break;
		case ColliderType::TURQUOISE_PAW:
			LOG("Collider turquoise paw");
			//WHATEVER
			break;

		case ColliderType::BELL:
			LOG("Collider bell paw");
			//WHATEVER
			break;
	}
	*/
}

