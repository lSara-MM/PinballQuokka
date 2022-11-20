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


	fondo = App->textures->Load("pinball/Fondo2.png");
	int Fondo[122] = {
	504, 825,
	503, 146,
	502, 136,
	497, 122,
	490, 112,
	482, 102,
	472, 92,
	460, 83,
	448, 77,
	429, 70,
	419, 68,
	142, 68,
	127, 72,
	111, 77,
	95, 86,
	83, 93,
	68, 104,
	56, 115,
	46, 125,
	39, 135,
	32, 153,
	32, 410,
	37, 417,
	48, 429,
	60, 440,
	74, 452,
	85, 459,
	92, 464,
	98, 474,
	101, 480,
	101, 489,
	95, 496,
	84, 499,
	72, 499,
	56, 495,
	40, 487,
	32, 483,
	32, 777,
	34, 784,
	38, 796,
	44, 802,
	51, 808,
	60, 815,
	72, 821,
	97, 832,
	129, 844,
	188, 850,
	272, 850,
	362, 848,
	411, 826,
	422, 818,
	431, 814,
	440, 807,
	448, 794,
	453, 781,
	455, 773,
	455, 252,
	457, 247,
	462, 246,
	466, 250,
	467, 826
	};

	int Oreja[44] = {
	171, 310,
	151, 292,
	134, 280,
	119, 277,
	108, 280,
	102, 287,
	100, 296,
	100, 377,
	101, 387,
	106, 394,
	116, 398,
	125, 397,
	135, 391,
	140, 384,
	141, 379,
	143, 353,
	146, 345,
	150, 338,
	156, 331,
	164, 328,
	170, 323,
	171, 316
	};

	int Oreja2[48] = {
	329, 308,
	344, 295,
	360, 283,
	369, 278,
	379, 277,
	386, 278,
	392, 282,
	397, 290,
	399, 296,
	400, 380,
	398, 387,
	392, 394,
	383, 398,
	374, 398,
	365, 393,
	359, 386,
	357, 380,
	356, 356,
	353, 346,
	348, 338,
	341, 331,
	333, 327,
	328, 322,
	327, 316
	};

	int Barra[14] = {
	413, 646,
	413, 739,
	302, 779,
	307, 795,
	422, 760,
	421, 646,
	417, 642
	};

	int Barra2[14] = {
	73, 647,
	73, 760,
	187, 796,
	195, 778,
	81, 739,
	81, 647,
	77, 642
	};

	int Triangle[20] = {
	132, 646,
	200, 703,
	201, 708,
	199, 715,
	193, 719,
	124, 703,
	119, 698,
	119, 654,
	121, 649,
	126, 646
	};

	int Triangle2[20] = {
	363, 647,
	295, 701,
	294, 706,
	295, 711,
	302, 716,
	372, 702,
	376, 699,
	377, 693,
	376, 650,
	370, 646
	};

	int Oval[40] = {
	193, 334,
	190, 338,
	188, 346,
	187, 356,
	186, 367,
	186, 380,
	186, 394,
	187, 407,
	188, 416,
	189, 422,
	193, 429,
	196, 424,
	198, 418,
	200, 407,
	201, 395,
	201, 379,
	201, 367,
	200, 355,
	199, 345,
	197, 339
	};

	int Oval2[40] = {
	193 + 58, 334,
	190 + 58, 338,
	188 + 58, 346,
	187 + 58, 356,
	186 + 58, 367,
	186 + 58, 380,
	186 + 58, 394,
	187 + 58, 407,
	188 + 58, 416,
	189 + 58, 422,
	193 + 58, 429,
	196 + 58, 424,
	198 + 58, 418,
	200 + 58, 407,
	201 + 58, 395,
	201 + 58, 379,
	201 + 58, 367,
	200 + 58, 355,
	199 + 58, 345,
	197 + 58, 339
	};

	int Oval3[40] = {
	193 + 58 + 57, 334,
	190 + 58 + 57, 338,
	188 + 58 + 57, 346,
	187 + 58 + 57, 356,
	186 + 58 + 57, 367,
	186 + 58 + 57, 380,
	186 + 58 + 57, 394,
	187 + 58 + 57, 407,
	188 + 58 + 57, 416,
	189 + 58 + 57, 422,
	193 + 58 + 57, 429,
	196 + 58 + 57, 424,
	198 + 58 + 57, 418,
	200 + 58 + 57, 407,
	201 + 58 + 57, 395,
	201 + 58 + 57, 379,
	201 + 58 + 57, 367,
	200 + 58 + 57, 355,
	199 + 58 + 57, 345,
	197 + 58 + 57, 339

	};

	chains.add(App->physics->CreateChain(0, 0, Fondo, 122, App->physics->STATIC, ColliderType::PLATFORM));

	b1 =  App->physics->CreateBouncyChain(0, 0, Oreja, 44, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b1);
	b2 = App->physics->CreateBouncyChain(0, 0, Oreja2, 48, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b2);
	b3 = App->physics->CreateBouncyChain(0, 0, Triangle, 20, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b3);
	b4 = App->physics->CreateBouncyChain(0, 0, Triangle2, 20, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b4);
	b5 = App->physics->CreateChain(0, 0, Oval, 40, App->physics->STATIC, ColliderType::OVAL);//crec que aquests no haurien de fer bounce
	chains.add(b5);
	b6 = App->physics->CreateChain(0, 0, Oval2, 40, App->physics->STATIC, ColliderType::OVAL);
	chains.add(b6);
	b7 = App->physics->CreateChain(0, 0, Oval3, 40, App->physics->STATIC, ColliderType::OVAL);
	chains.add(b7);
	b8 = App->physics->CreateBouncyCircle(379, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK);
	chains.add(b8);
	b9 = App->physics->CreateBouncyCircle(128, 554, 19, bounce, App->physics->STATIC, ColliderType::CHEEK);
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

	Purple_Paw = App->physics->CreateBouncyCircle(252, 136, 31, bounce, App->physics->STATIC, ColliderType::PURPLE_PAW);
	Green_Paw = App->physics->CreateBouncyCircle(143, 198, 31, bounce, App->physics->STATIC, ColliderType::GREEN_PAW);
	Turqupise_Paw = App->physics->CreateBouncyCircle(363, 198, 31, bounce, App->physics->STATIC, ColliderType::TURQUOISE_PAW);
	Pink_Paw = App->physics->CreateBouncyCircle(252, 256, 31, bounce, App->physics->STATIC, ColliderType::PINK_PAW);


	circles.add(Purple_Paw);
	circles.add(Green_Paw);
	circles.add(Turqupise_Paw);
	circles.add(Pink_Paw);


	chains.add(App->physics->CreateRectangleSensor(280, 380, 40, 1, ColliderType::OVAL));//sensor típic passar carril sumar punts, animació especial?
	chains.add(App->physics->CreateRectangleSensor(222, 380, 40, 1, ColliderType::OVAL));

	chains.add(App->physics->CreateRectangleSensor(250,820, 330, 1, ColliderType::BELL));//"mort jugador"

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, ColliderType::UNKNOWN);
	
	// Add this module (ModuleScene) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleScene::OnCollision()
	//lower_ground_sensor->listener = this;
	
	// Ball
	ballPlayer = App->physics->CreateCircle(483, 571, 16, App->physics->DYNAMIC, ColliderType::BALL);
	circles.add(ballPlayer);
	circles.getLast()->data->listener = this;

	// Audio

	audiohit = App->audio->LoadFx("pinball/hit.ogg");

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

	//Slingershot
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

		int triangle[6] = {
				0, 0,
				400, 0,
				200, 200,//valors arbirtaris, canviar en funció mapa
		};
		slingershots.add(App->physics->CreateBouncyChain(App->input->GetMouseX(), App->input->GetMouseY(), triangle, 6, 2.0, App->physics->STATIC, ColliderType::UNKNOWN));
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
			App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());

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

		case ColliderType::EARS:
			LOG("Collider ears");
			App->player->score += 50;
			//WHATEVER
			break;

		case ColliderType::ORANGE_BUMPER:
			LOG("Collider orange bumper");
			App->player->score += 100;
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
			App->player->numBalls--;
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
			LOG("Collider slingershot");
			//WHATEVER
			break;
	}
	
}

bool ModuleScene::loseGame()
{
	for (int i = 0; i < 10; i++)
	{
		if (App->scene_lead->leaderboard[i] < App->player->score)
		{
			App->scene_lead->leaderboard[i] = App->player->score;
			break;
		}
	}

	App->scene_lead->currentScore = App->player->score;
	App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_intro, 90);

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
		if (App->scene_lead->leaderboard[9] < App->player->score)
		{
			App->scene_lead->leaderboard[9] = App->player->score;

		}

		App->scene_lead->currentScore = App->player->score;
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_lead, 0);
	}


	// GodMode
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->physics->debug = !App->physics->debug;
		normGrav = true;
	}
	if (App->physics->debug) { App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 0)); }
	if (!App->physics->debug) 
	{ 
		if (normGrav) 
		{
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, -GRAVITY_Y));
		}
		normGrav = false;
	}

	// Spawn bola donde el mouse
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		circles.getLast()->data->body->DestroyFixture(circles.getLast()->data->body->GetFixtureList());
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 16, App->physics->DYNAMIC, ColliderType::BALL));
		circles.getLast()->data->listener = this;
	}
	
	// Insta lose
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		loseGame();
	}

	// Score++
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		App->player->score++;
	}

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
			App->scene->bounce = 1;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			App->scene->bounce = 2;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			App->scene->bounce = 3;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			App->scene->bounce = 4;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			App->scene->bounce = 5;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			App->scene->bounce = 6;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			App->scene->bounce = 7;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			App->scene->bounce = 8;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			App->scene->bounce = 9;
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
