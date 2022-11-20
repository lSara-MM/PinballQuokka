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

	lose = true; 
	
	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	ball = App->textures->Load("pinball/ball_yarn.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map = App->textures->Load("pinball/muelle.png");

	fondo = App->textures->Load("pinball/Pinball2.png");
	texLoseCat = App->textures->Load("pinball/loseBg.png");
	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   .,:!?()-" };
	subtitleFont = App->renderer->LoadFont("Pinball/font_CatPaw32.png", lookupTable2, 6, 13); // 6 = rows 13 = columns

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
	192 + 5, 646,
	240 + 5, 699,
	240 + 5, 708,
	233 + 5, 712,
	186 + 5, 697,
	181 + 5, 692,
	182 + 5, 651,
	186 + 5, 646
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

	//Scene colliders
	backGround = App->physics->CreateChain(0, 0, Fondo, 112, App->physics->STATIC, ColliderType::PLATFORM);
	chains.add(backGround);

	b1 =  App->physics->CreateBouncyChain(0, 0, Oreja, 44, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b1);
	b2 = App->physics->CreateBouncyChain(0, 0, Oreja2, 48, bounce, App->physics->STATIC, ColliderType::EARS);
	chains.add(b2);
	b3 = App->physics->CreateBouncyChain(0, 0, Triangle, 16, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b3);
	b4 = App->physics->CreateBouncyChain(0, 0, Triangle2, 16, bounce, App->physics->STATIC, ColliderType::ORANGE_BUMPER);
	chains.add(b4);
	b5 = App->physics->CreateChain(0, 0, Oval, 40, App->physics->STATIC, ColliderType::OVAL);
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

	b11 = App->physics->CreateChain(0, 0, Barra, 14, App->physics->STATIC, ColliderType::ROD);
	chains.add(b11);
	b12 = App->physics->CreateChain(0, 0, Barra2, 14, App->physics->STATIC, ColliderType::ROD);
	chains.add(b12);

	Purple_Paw = App->physics->CreateBouncyCircle(47, 490, 28, bounce, App->physics->STATIC, ColliderType::PURPLE_PAW);
	Green_Paw = App->physics->CreateBouncyCircle(232, 221, 31, bounce, App->physics->STATIC, ColliderType::GREEN_PAW);
	Turqupise_Paw = App->physics->CreateBouncyCircle(398, 218, 31, bounce, App->physics->STATIC, ColliderType::TURQUOISE_PAW);
	Pink_Paw = App->physics->CreateBouncyCircle(316, 145, 31, bounce, App->physics->STATIC, ColliderType::PINK_PAW);


	circles.add(Purple_Paw);
	circles.add(Green_Paw);
	circles.add(Turqupise_Paw);
	circles.add(Pink_Paw);


	sensor_1 = App->physics->CreateRectangleSensor(318, 537, 40, 1, ColliderType::NOSE);
	chains.add(sensor_1);
	sensor_2 = App->physics->CreateRectangleSensor(310, 850, 350, 1, ColliderType::BELL);//"mort jugador"
	chains.add(sensor_2);


	// Ball
	bola = App->physics->CreateCircle(550, 685, 16, App->physics->DYNAMIC, ColliderType::BALL);
	circles.add(bola);
	circles.getLast()->data->listener = this;

	// Audio
	audiohit = App->audio->LoadFx("pinball/hit.ogg");
	audioimpact = App->audio->LoadFx("pinball/impact.ogg");
	audiomiau = App->audio->LoadFx("pinball/meow.ogg");
	audiolose = App->audio->LoadFx("pinball/gameOver.ogg");


	if (retry == true) {
		App->audio->PlayMusic("pinball/Music.ogg", 0);
	}

	greenP = false;
	purpleP = false; 
	turquoiseP = false; 
	pinkP = false;
	lifeLose = false;
	godMode = false;
	retry = false;
	lose = true;
	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(ball);
	App->textures->Unload(fondo);
	App->textures->Unload(map);
	App->textures->Unload(fondo);

	App->renderer->UnLoadFont(subtitleFont);
	
	greenP = false;
	purpleP = false;
	turquoiseP = false;
	pinkP = false;

	
	if (b1->body->GetFixtureList())
	{
		b1->body->DestroyFixture(b1->body->GetFixtureList());
	}


	if (b2->body->GetFixtureList())
	{
		b2->body->DestroyFixture(b2->body->GetFixtureList());
	}
		
	if (b3->body->GetFixtureList())
	{
		b3->body->DestroyFixture(b3->body->GetFixtureList());
	}

	if (b4->body->GetFixtureList())
	{
		b4->body->DestroyFixture(b4->body->GetFixtureList());
	}

	if (b5->body->GetFixtureList())
	{
		b5->body->DestroyFixture(b5->body->GetFixtureList());
	}

	if (b6->body->GetFixtureList())
	{
		b6->body->DestroyFixture(b6->body->GetFixtureList());
	}

	if (b7->body->GetFixtureList())
	{
		b7->body->DestroyFixture(b7->body->GetFixtureList());
	}

	if (b8->body->GetFixtureList())
	{
		b8->body->DestroyFixture(b8->body->GetFixtureList());
	}

	if (b9->body->GetFixtureList())
	{
		b9->body->DestroyFixture(b9->body->GetFixtureList());
	}

	if (b10->body->GetFixtureList())
	{
		b10->body->DestroyFixture(b10->body->GetFixtureList());
	}

	if (b11->body->GetFixtureList())
	{
		b11->body->DestroyFixture(b11->body->GetFixtureList());
	}

	if (b12->body->GetFixtureList())
	{
		b12->body->DestroyFixture(b12->body->GetFixtureList());
	}

	if (backGround->body->GetFixtureList())
	{
		backGround->body->DestroyFixture(backGround->body->GetFixtureList());
	}

	if (sensor_1->body->GetFixtureList())
	{
		sensor_1->body->DestroyFixture(sensor_1->body->GetFixtureList());
	}

	if (sensor_2->body->GetFixtureList())
	{
		sensor_2->body->DestroyFixture(sensor_2->body->GetFixtureList());
	}

	if (bola->body->GetFixtureList())
	{
		bola->body->DestroyFixture(bola->body->GetFixtureList());
	}

	App->player->Disable();
	return true;
}

update_status ModuleScene::Update()
{
	//Dibujar el mapa
	App->renderer->Blit(fondo, 0, 0);

	debug();
	loseLife();

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
	if (App->player->numBalls == 0)
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


	switch (bodyB->ctype)
	{
		case ColliderType::PLATFORM:
			LOG("Collider platform");
			break;

		case ColliderType::NOSE:
			LOG("Collider nose");
			App->audio->PlayFx(audiomiau);
			break;

		case ColliderType::EARS:
			LOG("Collider ears");
			if (App->player->numBalls != 0) { App->player->score += 50; }
			break;

		case ColliderType::ORANGE_BUMPER:
			LOG("Collider orange bumper");
			if (App->player->numBalls != 0) { App->player->score += 100; }
			App->audio->PlayFx(audioimpact);
			break;

		case ColliderType::OVAL:
			LOG("Collider oval");
			if (App->player->numBalls != 0) { App->player->score += 50; }
			break;

		case ColliderType::GREEN_PAW:
			LOG("Collider green paw");
			if (App->player->numBalls != 0) { App->player->score += 150; }
			App->audio->PlayFx(audiohit);
			if (greenP == false)
			{
				App->player->comboPaws++;
				greenP = true;
			}
		
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
			break;
		case ColliderType::TURQUOISE_PAW:
			LOG("Collider turquoise paw");
			if (App->player->numBalls != 0) { App->player->score += 150; }
			App->audio->PlayFx(audiohit);
			if (turquoiseP == false)
			{
				App->player->comboPaws++;
				turquoiseP = true;
			}
	
			break;

		case ColliderType::PINK_PAW:
			LOG("Collider pink paw");
			if (App->player->numBalls != 0) { App->player->score += 150; }
			App->audio->PlayFx(audiohit);
			if (pinkP == false)
			{
				App->player->comboPaws++;
				pinkP = true;
			}
		
			break;

		case ColliderType::BELL:
			LOG("Collider bell");
			if (!App->physics->debug)
				lifeLose = true;
			break;

		case ColliderType::CHEEK:
			LOG("Collider cheek");
			if (App->player->numBalls != 0) { App->player->score += 100; }
		break;

		case ColliderType::ROD:
			LOG("Collider rod");
			break;

		case ColliderType::SLINGERSHOT:
			App->audio->PlayFx(audioimpact);
			LOG("Collider slingershot");
			break;
	}
}

bool ModuleScene::loseGame()
{
	App->audio->PauseMusic();
	if (lose == true) {
		App->audio->PlayFx(audiolose);
		lose = false;
	}
	App->renderer->Blit(texLoseCat, 0, 0);

	string s_num = std::to_string(App->player->score);
	const char* ch_num = s_num.c_str();
	App->renderer->BlitText(120, 100, subtitleFont, "Score: ");
	App->renderer->BlitText(300, 100, subtitleFont, ch_num);
	
	bGoRanks = { 50, 200, 250, 40};
	bRetry = { 350, 200, 200, 40 };

	// retry
	if (retry == false)
	{
		App->renderer->DrawQuad(bGoRanks, 60, 100, 255, 100);
		App->renderer->DrawQuad(bRetry, 255, 255, 255, 70);
	}
	else
	{
		App->renderer->DrawQuad(bGoRanks, 255, 255, 255, 70);
		App->renderer->DrawQuad(bRetry, 60, 100, 255, 100);
	}

	App->renderer->BlitText(55, 208, subtitleFont, "Leaderboard", 0.7f);
	App->renderer->BlitText(370, 204, subtitleFont, "Retry");

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && retry == false)
	{

		App->fade->FadeToBlack(this, (Module*)App->scene_lead, 90);
	}
	// non retry
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && retry == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		retry = !retry;

	// Score
	if (App->scene_lead->leaderboard[9] < App->player->score) { App->scene_lead->leaderboard[9] = App->player->score; }
	App->scene_lead->currentScore = App->player->score;

	App->player->Disable();
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
		circles.add(App->physics->CreateCircle(550, 685, 16, App->physics->DYNAMIC, ColliderType::BALL));
		circles.getLast()->data->listener = this;

		lifeLose = false;
		LOG("Life lost!");
	}	
}

void ModuleScene::debug()
{
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)	// delete after
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_intro, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		if (App->scene_lead->leaderboard[9] < App->player->score) { App->scene_lead->leaderboard[9] = App->player->score; }

		App->scene_lead->currentScore = App->player->score;
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene_lead, 0);
	}

	// GodMode
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->physics->debug = !App->physics->debug;
		godMode = !godMode;
	}
	if (App->physics->debug && godMode) { App->physics->world->SetGravity(b2Vec2(GRAVITY_X, 0)); }
	if (!App->physics->debug && !godMode && App->physics->world->GetGravity().y == 0) { App->physics->world->SetGravity(b2Vec2(GRAVITY_X, -GRAVITY_Y)); }

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
		App->audio->PlayFx(audiomiau);
		//App->physics->world->DestroyBody(circles.getLast()->data->body);
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
	App->renderer->BlitText(450, 53, subtitleFont, "GRAVITY ", 0.4f);
	App->renderer->BlitText(540, 53, subtitleFont, ("%.2f; ", g), 0.4f);

	// Gravity change
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		grav = true;
		LOG("GRAVITY %f", App->physics->world->GetGravity().y);
	}	
	if (grav)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			App->physics->world->SetGravity(b2Vec2(GRAVITY_X, GRAVITY_Y));
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
	App->renderer->BlitText(90, 54, subtitleFont, "FPS", 0.4f);
	App->renderer->BlitText(130, 54, subtitleFont, ch_num, 0.4f);

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
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			frames = FRAMES;
			fps = false;
		}
	}

	string bouncing = std::to_string(bounce);
	const char* b = bouncing.c_str();
	App->renderer->BlitText(200, 53, subtitleFont, "BOUNCINESS", 0.4f);
	App->renderer->BlitText(320, 53, subtitleFont, ("%.2f; ", b), 0.4f);

	// Bouncing coefficient
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		boing = true;
		LOG("Boing %f", bounce);
	}
	if (boing)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			bounce = 0;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			bounce = 0.3;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
			bounce = 0.6;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
			bounce = 0.9;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
			bounce = 1.2;
			fps = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
			bounce = 1.5;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
			bounce = 1.8;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
			bounce = 2.1;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
			bounce = 2.4;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
			bounce = 2.7;
			boing = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			bounce = BOUNCE;
			boing = false;
		}

		b1->body->GetFixtureList()->SetRestitution(bounce);
		b2->body->GetFixtureList()->SetRestitution(bounce);
		b3->body->GetFixtureList()->SetRestitution(bounce);
		b4->body->GetFixtureList()->SetRestitution(bounce);
		b8->body->GetFixtureList()->SetRestitution(bounce);
		b9->body->GetFixtureList()->SetRestitution(bounce);

		Green_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Pink_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Purple_Paw->body->GetFixtureList()->SetRestitution(bounce);
		Turqupise_Paw->body->GetFixtureList()->SetRestitution(bounce);
	}

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN && !godMode) {
		App->physics->debug = !App->physics->debug;
	}
}
