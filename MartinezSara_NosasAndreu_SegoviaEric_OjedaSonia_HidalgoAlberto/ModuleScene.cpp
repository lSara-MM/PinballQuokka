#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include "ModuleLeaderboard.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleLeaderboard.h"

#include <iostream>
using namespace std;
#include <sstream>

#include <stdlib.h> 


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// Initialise all the internal class variables, at least to NULL pointer
	ball = NULL;
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
	App->physics->Enable();
	App->player->Enable();

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	ball = App->textures->Load("pinball/ball_yarn.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map = App->textures->Load("pinball/muelle.png");

	fondo = App->textures->Load("pinball/Pinball2.png");
	//texLoseCat = App->textures->Load("pinball/.png");
	bgColor = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };

	int Fondo[112] = {
    571, 821,
	571, 143,
	569, 133,
	564, 122,
	555, 110,
	544, 97,
	531, 86,
	515, 78,
	497, 71,
	489, 69,
	208, 68,
	183, 69,
	151, 74,
	128, 78,
	104, 84,
	83, 93,
	63, 107,
	40, 130,
	22, 161,
	13, 186,
	7, 222,
	6, 250,
	6, 286,
	6, 320,
	9, 352,
	18, 374,
	18, 505,
	101, 574,
	101, 780,
	105, 791,
	112, 803,
	126, 813,
	132, 817,
	157, 862,
	171, 882,
	288, 886,
	354, 884,
	457, 888,
	490, 818,
	500, 813,
	511, 803,
	517, 791,
	523, 776,
	523, 480,
	488, 491,
	480, 488,
	475, 482,
	474, 473,
	479, 467,
	523, 452,
	523, 193,
	527, 189,
	532, 189,
	535, 194,
	535, 868,
	574, 868
	};

	int Oreja[44] = {
    171 + 50, 310,
	151 + 50, 292,
	134 + 50, 280,
	119 + 50, 277,
	108 + 50, 280,
	102 + 50, 287,
	100 + 50, 296,
	100 + 50, 377,
	101 + 50, 387,
	106 + 50, 394,
	116 + 50, 398,
	125 + 50, 397,
	135 + 50, 391,
	140 + 50, 384,
	141 + 50, 379,
	143 + 50, 353,
	146 + 50, 345,
	150 + 50, 338,
	156 + 50, 331,
	164 + 50, 328,
	170 + 50, 323,
	171 + 50, 316
	};

	int Oreja2[48] = {
	329 + 82, 308,
	344 + 82, 295,
	360 + 82, 283,
	369 + 82, 278,
	379 + 82, 277,
	386 + 82, 278,
	392 + 82, 282,
	397 + 82, 290,
	399 + 82, 296,
	400 + 82, 380,
	398 + 82, 387,
	392 + 82, 394,
	383 + 82, 398,
	374 + 82, 398,
	365 + 82, 393,
	359 + 82, 386,
	357 + 82, 380,
	356 + 82, 356,
	353 + 82, 346,
	348 + 82, 338,
	341 + 82, 331,
	333 + 82, 327,
	328 + 82, 322,
	327 + 82, 316
	};

	int Barra[14] = {
	489, 646,
	489, 760,
	391, 783,
	384, 767,
	481, 739,
	481, 645,
	485, 642
	};


	int Barra2[14] = {
	141, 645,
	141, 760,
	235, 786,
	243, 768,
	149, 739,
	149, 646,
	145, 642
	};

	int Triangle[16] = {
	192, 646,
	240, 699,
	240, 708,
	233, 712,
	186, 697,
	181, 692,
	182, 651,
	186, 646
	};

	int Triangle2[16] = {
	437, 648,
	392, 696,
	392, 705,
	397, 709,
	443, 697,
	447, 691,
	446, 649,
	441, 645
	};

	int Oval[40] = {
	193 + 66, 334,
	190 + 66, 338,
	188 + 66, 346,
	187 + 66, 356,
	186 + 66, 367,
	186 + 66, 380,
	186 + 66, 394,
	187 + 66, 407,
	188 + 66, 416,
	189 + 66, 422,
	193 + 66, 429,
	196 + 66, 424,
	198 + 66, 418,
	200 + 66, 407,
	201 + 66, 395,
	201 + 66, 379,
	201 + 66, 367,
	200 + 66, 355,
	199 + 66, 345,
	197 + 66, 339
	};

	int Oval2[40] = {
	193 + 58 + 66, 334,
	190 + 58 + 66, 338,
	188 + 58 + 66, 346,
	187 + 58 + 66, 356,
	186 + 58 + 66, 367,
	186 + 58 + 66, 380,
	186 + 58 + 66, 394,
	187 + 58 + 66, 407,
	188 + 58 + 66, 416,
	189 + 58 + 66, 422,
	193 + 58 + 66, 429,
	196 + 58 + 66, 424,
	198 + 58 + 66, 418,
	200 + 58 + 66, 407,
	201 + 58 + 66, 395,
	201 + 58 + 66, 379,
	201 + 58 + 66, 367,
	200 + 58 + 66, 355,
	199 + 58 + 66, 345,
	197 + 58 + 66, 339
	};

	int Oval3[40] = {
	193 + 58 + 57 + 66, 334,
	190 + 58 + 57 + 66, 338,
	188 + 58 + 57 + 66, 346,
	187 + 58 + 57 + 66, 356,
	186 + 58 + 57 + 66, 367,
	186 + 58 + 57 + 66, 380,
	186 + 58 + 57 + 66, 394,
	187 + 58 + 57 + 66, 407,
	188 + 58 + 57 + 66, 416,
	189 + 58 + 57 + 66, 422,
	193 + 58 + 57 + 66, 429,
	196 + 58 + 57 + 66, 424,
	198 + 58 + 57 + 66, 418,
	200 + 58 + 57 + 66, 407,
	201 + 58 + 57 + 66, 395,
	201 + 58 + 57 + 66, 379,
	201 + 58 + 57 + 66, 367,
	200 + 58 + 57 + 66, 355,
	199 + 58 + 57 + 66, 345,
	197 + 58 + 57 + 66, 339

	};

	int tail[48] = {
    125, 115,
    87, 153,
    71, 183,
    58, 220,
    52, 248,
    51, 289,
    56, 325,
    65, 358,
    77, 386,
    101, 417,
    134, 450,
    160, 468,
    153, 458,
    131, 441,
    106, 417,
    84, 390,
    71, 362,
    61, 329,
    55, 295,
    55, 256,
    59, 230,
    69, 196,
    84, 164,
    104, 139
	};


	chains.add(App->physics->CreateChain(0, 0, Fondo, 112, App->physics->STATIC, ColliderType::PLATFORM));

	b1 =  App->physics->CreateBouncyChain(0, 0, Oreja, 44, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b1);
	b2 = App->physics->CreateBouncyChain(0, 0, Oreja2, 48, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b2);
	b3 = App->physics->CreateBouncyChain(0, 0, Triangle, 16, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b3);
	b4 = App->physics->CreateBouncyChain(0, 0, Triangle2, 16, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b4);
	b5 = App->physics->CreateChain(0, 0, Oval, 40, App->physics->STATIC, ColliderType::OVAL);//crec que aquests no haurien de fer bounce
	chains.add(b5);
	b6 = App->physics->CreateChain(0, 0, Oval2, 40, App->physics->STATIC, ColliderType::OVAL);
	chains.add(b6);
	b7 = App->physics->CreateChain(0, 0, Oval3, 40, App->physics->STATIC, ColliderType::OVAL);
	chains.add(b7);
	b10 = App->physics->CreateChain(0, 0, tail, 48, App->physics->STATIC, ColliderType::PLATFORM);
	chains.add(b10);
	b8 = App->physics->CreateBouncyCircle(447, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK);
	chains.add(b8);
	b9 = App->physics->CreateBouncyCircle(196, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK);
	chains.add(b9);

	//chains.add(App->physics->CreateBouncyChain(0, 0, Oreja, 44, bounce, App->physics->STATIC, ColliderType::EARS));
	//chains.add(App->physics->CreateBouncyChain(0, 0, Oreja2, 48, bounce, App->physics->STATIC, ColliderType::EARS));
	chains.add(App->physics->CreateChain(0, 0, Barra, 14, App->physics->STATIC, ColliderType::ROD));
	chains.add(App->physics->CreateChain(0, 0, Barra2, 14, App->physics->STATIC, ColliderType::ROD));
	//chains.add(App->physics->CreateBouncyChain(0, 0, Triangle, 20, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER));
	//chains.add(App->physics->CreateBouncyChain(0, 0, Triangle2, 20, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER));//canviar els valos de bounce per ajustar rebot
	//chains.add(App->physics->CreateBouncyChain(0, 0, Oval, 40, bounce, App->physics->STATIC, ColliderType::OVAL));
	//chains.add(App->physics->CreateBouncyChain(0, 0, Oval2, 40, bounce, App->physics->STATIC, ColliderType::OVAL));
	//chains.add(App->physics->CreateBouncyChain(0, 0, Oval3, 40, bounce, App->physics->STATIC, ColliderType::OVAL));

	//circles.add(App->physics->CreateBouncyCircle(379, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK));
	//circles.add(App->physics->CreateBouncyCircle(128, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK));

	Purple_Paw = App->physics->CreateBouncyCircle(47, 490, 28, bounce, App->physics->STATIC, ColliderType::PURPLE_PAW);
	Green_Paw = App->physics->CreateBouncyCircle(232, 221, 31, bounce, App->physics->STATIC, ColliderType::GREEN_PAW);
	Turqupise_Paw = App->physics->CreateBouncyCircle(398, 218, 31, bounce, App->physics->STATIC, ColliderType::TURQUOISE_PAW);
	Pink_Paw = App->physics->CreateBouncyCircle(316, 145, 31, bounce, App->physics->STATIC, ColliderType::PINK_PAW);


	circles.add(Purple_Paw);
	circles.add(Green_Paw);
	circles.add(Turqupise_Paw);
	circles.add(Pink_Paw);


	//chains.add(App->physics->CreateRectangleSensor(280, 380, 40, 1, ColliderType::OVAL));//sensor típic passar carril sumar punts, animació especial?
	chains.add(App->physics->CreateRectangleSensor(318, 537, 40, 1, ColliderType::NOSE));

	chains.add(App->physics->CreateRectangleSensor(250,820, 330, 1, ColliderType::BELL));//"mort jugador"

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, ColliderType::UNKNOWN);
	
	// Add this module (ModuleScene) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleScene::OnCollision()
	//lower_ground_sensor->listener = this;
	
	// Ball
	circles.add(App->physics->CreateCircle(483, 571, 16, App->physics->DYNAMIC, ColliderType::BALL));
	circles.getLast()->data->listener = this;

	// Audio
	audiohit = App->audio->LoadFx("pinball/hit.ogg");
	audioimpact = App->audio->LoadFx("pinball/impact.ogg");
	audiomiau = App->audio->LoadFx("pinball/meow.ogg");

	greenP = false;
	purpleP = false; 
	turquoiseP = false; 
	pinkP = false;
	lifeLose = false;

	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(ball);
	App->textures->Unload(fondo);
	App->textures->Unload(map);
	App->textures->Unload(fondo);

	greenP = false;
	purpleP = false;
	turquoiseP = false;
	pinkP = false;

	p2List_item<PhysBody*>* circleItem;

	circleItem = circles.start;

	while (circleItem != NULL)
	{
		if (circleItem->data != NULL)
		{					  
			delete circleItem->data;
			circleItem->data = NULL;
		}
		circleItem = circleItem->next;
	}

	p2List_item<PhysBody*>* chianItem;

	chianItem = chains.start;

	while (chianItem != NULL)
	{
		if (chianItem->data != NULL)
		{
			delete chianItem->data;
			chianItem->data = NULL;
		}
		chianItem = chianItem->next;
	}

	circles.clear();
	chains.clear();

	App->player->Disable();
	
	return true;
}

update_status ModuleScene::Update()
{
	//Dibujar el mapa
	App->renderer->Blit(fondo, 0, 0);
	//App->renderer->Blit(map,0,0);

	debug();
	loseLife();


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

	//Slingershots
	p2List_item<PhysBody*>* c;
	c = slingershots.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		//App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// Raycasts -----------------
	if (ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	// Ball render

	int ballX, ballY;
	circles.getLast()->data->GetPosition(ballX, ballY);
	App->renderer->Blit(ball, ballX, ballY, NULL, 1, 1.0f, circles.getLast()->data->GetRotation());

	
	if (App->player->comboPaws == 4)
	{
		App->player->score += 500;
		App->player->comboPaws = 0;
		greenP = false;
		purpleP = false;
		turquoiseP = false;
		pinkP = false;
		LOG("COMBO! Score: %d", App->player->score);
	}


	// Lifes left
	if (App->player->numBalls == 0 && !App->physics->debug)
		loseGame();
	if (App->player->numBalls >= 1)
		App->renderer->Blit(ball, 10, 10);
	if (App->player->numBalls >= 2)
		App->renderer->Blit(ball, 10, 50);
	if (App->player->numBalls == 3)
		App->renderer->Blit(ball, 10, 90);

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	
	//App->audio->PlayFx(bonus_fx);

	switch (bodyB->ctype)
	{
		case ColliderType::PLATFORM:
			LOG("Collider platform");
			
			//WHATEVER
			break;

		case ColliderType::NOSE:
			LOG("Collider nose");
			App->audio->PlayFx(audiomiau);

			//WHATEVER
			break;

		case ColliderType::EARS:
			LOG("Collider ears");
			App->player->score += 50;
			//WHATEVER
			break;

		case ColliderType::ORANGE_BUMPER:
			LOG("Collider orange bumper");
			App->player->score += 100;
			App->audio->PlayFx(audioimpact);
			//WHATEVER
			break;

		case ColliderType::OVAL:
			LOG("Collider oval");
			App->player->score += 50;
			//WHATEVER
			break;

		case ColliderType::GREEN_PAW:
			LOG("Collider green paw");
			App->player->score += 150;
			App->audio->PlayFx(audiohit); 
			if (greenP == false)
			{
				App->player->comboPaws++;
				greenP = true;
			}
			else if (greenP == true)
			{
				App->player->comboPaws--;
				greenP = false;
			}
			//WHATEVER
			break;
		
		case ColliderType::PURPLE_PAW:
			LOG("Collider purple paw");
			App->player->score += 150;
			App->audio->PlayFx(audiohit);
			if (purpleP == false)
			{
				App->player->comboPaws++;
				purpleP = true;
			}
			else if (purpleP == true)
			{
				App->player->comboPaws--;
				purpleP = false;
			}
			//WHATEVER
			break;
		case ColliderType::TURQUOISE_PAW:
			LOG("Collider turquoise paw");
			App->player->score += 150;
			App->audio->PlayFx(audiohit);
			if (turquoiseP == false)
			{
				App->player->comboPaws++;
				turquoiseP = true;
			}
			else if (turquoiseP == true)
			{
				App->player->comboPaws--;
				turquoiseP = false;
			}
			//WHATEVER
			break;

		case ColliderType::PINK_PAW:
			LOG("Collider pink paw");
			App->player->score += 150;
			App->audio->PlayFx(audiohit);
			if (pinkP == false)
			{
				App->player->comboPaws++;
				pinkP = true;
			}
			else if (pinkP == true)
			{
				App->player->comboPaws--;
				pinkP = false;
			}
			//WHATEVER
			break;

		case ColliderType::BELL:
			LOG("Collider bell");
			lifeLose = true;

			//WHATEVER
			break;

		case ColliderType::CHEEK:
			LOG("Collider cheek");
			App->player->score += 100;
			//WHATEVER
			break;

		case ColliderType::ROD:
			LOG("Collider rod");
			//WHATEVER
			break;

		case ColliderType::SLINGERSHOT:
			App->audio->PlayFx(audioimpact);
			LOG("Collider slingershot");
			//WHATEVER
			break;
	}
	
}

bool ModuleScene::loseGame()
{
	//App->physics->world->DestroyBody(circles.getLast()->data->body);
	//gameOver = true;
	
	App->player->Disable();
	App->renderer->DrawQuad(bgColor, 255, 255, 255);

	if (App->scene_lead->leaderboard[9] < App->player->score) { App->scene_lead->leaderboard[9] = App->player->score; }
	App->scene_lead->currentScore = App->player->score;

	// add losing screen
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_intro, 90);
	}

	return true;
}

void ModuleScene::loseLife() {

	if (lifeLose == true) {
		App->player->numBalls--;

		circles.getLast()->data->body->DestroyFixture(circles.getLast()->data->body->GetFixtureList());
		circles.add(App->physics->CreateCircle(483, 571, 16, App->physics->DYNAMIC, ColliderType::BALL));
		circles.getLast()->data->listener = this;

		lifeLose = false;
		LOG("Life lost!");
	}
	
}

void ModuleScene::debug()
{
	// If user presses SPACE, enable RayCast
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// Enable raycast mode
		ray_on = !ray_on;

		// Origin point of the raycast is be the mouse current position now (will not change)
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}


	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)	// delete after
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_intro, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)	// delete after
	{
		if (App->scene_lead->leaderboard[9] < App->player->score) { App->scene_lead->leaderboard[9] = App->player->score; }

		App->scene_lead->currentScore = App->player->score;
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_lead, 0);
	}

	// GodMode
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->physics->debug = !App->physics->debug;
	}
	if (App->physics->debug) { App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 0)); }
	if (!App->physics->debug) { App->physics->world->SetGravity(b2Vec2(GRAVITY_X, -GRAVITY_Y)); }

	// Spawn bola donde el mouse
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 16, App->physics->DYNAMIC, ColliderType::BALL));
		circles.getLast()->data->listener = this;
	}
	
	// Insta lose
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		App->player->numBalls = 0;
		loseGame();
	}

	// Score++
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		App->player->score++;
	}

	string gravity = std::to_string((int)App->physics->world->GetGravity().y);
	const char* g = gravity.c_str();
	App->renderer->BlitText(390, 53, App->scene_lead->titleFont, "GRAVITY ", 0.4f);
	App->renderer->BlitText(480, 53, App->scene_lead->titleFont, ("%.2f; ", g), 0.4f);

	// Gravity change
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		grav = true;
		LOG("GRAVITY %f", App->physics->world->GetGravity().y);
	}	
	if (grav)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, -5));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 1));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 2));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 3));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 4));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 5));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 6));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 7));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 8));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 9));
			grav = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, -GRAVITY_Y));
			grav = false;
		}
	}

	// FPS Change
	string s_num = std::to_string((int)frames);
	const char* ch_num = s_num.c_str();
	App->renderer->BlitText(45, 54, App->scene_lead->titleFont, "FPS", 0.4f);
	App->renderer->BlitText(95, 54, App->scene_lead->titleFont, ch_num, 0.4f);

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		fps = true;
		LOG("frames %f", frames);
	}
	if (fps)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			frames = 0;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			frames = 10;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			frames = 20;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			frames = 30;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			frames = 40;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			frames = 50;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			frames = 60;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			frames = 70;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			frames = 80;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			frames = 90;
			fps = false;
		}
	}

	string bouncing = std::to_string(App->scene->bounce);
	const char* b = bouncing.c_str();
	App->renderer->BlitText(150, 53, App->scene_lead->titleFont, "BOUNCINESS", 0.4f);
	App->renderer->BlitText(280, 53, App->scene_lead->titleFont, ("%.2f; ", b), 0.4f);

	// Bouncing coefficient
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		boing = true;
		LOG("Boing %f", App->scene->bounce);
	}
	if (boing)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			App->scene->bounce = 0;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			App->scene->bounce = 0.3;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			App->scene->bounce = 0.6;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			App->scene->bounce = 0.9;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			App->scene->bounce = 1.2;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			App->scene->bounce = 1.5;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			App->scene->bounce = 1.8;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			App->scene->bounce = 2.1;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			App->scene->bounce = 2.4;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			App->scene->bounce = 2.7;
			boing = false;
		}

		b1->body->GetFixtureList()->SetRestitution(bounce);
		b2->body->GetFixtureList()->SetRestitution(bounce);
		b3->body->GetFixtureList()->SetRestitution(bounce);
		b4->body->GetFixtureList()->SetRestitution(bounce);
		/*b5->body->GetFixtureList()->SetRestitution(bounce);//crec que aquests no haurien de fer bounce
		b6->body->GetFixtureList()->SetRestitution(bounce);
		b7->body->GetFixtureList()->SetRestitution(bounce);*/
		b8->body->GetFixtureList()->SetRestitution(bounce);
		b9->body->GetFixtureList()->SetRestitution(bounce);

		Green_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Pink_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Purple_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Turqupise_Paw->body->GetFixtureList()->SetRestitution(bounce);
	}
}
