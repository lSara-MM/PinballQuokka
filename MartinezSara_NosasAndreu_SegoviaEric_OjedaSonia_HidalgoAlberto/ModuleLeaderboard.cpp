#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleLeaderboard.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

#include <iostream>
using namespace std;
#include <sstream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "Animation.h"

ModuleLeaderboard::ModuleLeaderboard(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	animLurkingCat.PushBack({ 0, 0, 256, 192 });
	animLurkingCat.PushBack({ 0, 0, 256, 192 });
	animLurkingCat.PushBack({ 0, 0, 256, 192 });

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			animLurkingCat.PushBack({ 256 * j, 192 * i, 256, 192 });
			if (i == 3 && j == 3) { break; }
		}
	}
	for (int i = 7; i > 0; i--)
	{
		animLurkingCat.PushBack({ 256 * i, 0, 256, 192 });
	}
	animLurkingCat.speed = 0.2f;
}

ModuleLeaderboard::~ModuleLeaderboard()
{
	// You should do some memory cleaning here, if required
}

bool ModuleLeaderboard::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	//bgTexture = App->textures->Load("pinball/map.png");
	texLurkingCat = App->textures->Load("pinball/ss_LurkingCat.png");
	bgColor = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };


	// Load Font
	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789   .,:!?()-" };
	titleFont = App->renderer->LoadFont("Pinball/font_QuietMeows.png", lookupTable1, 4, 13); // 4 = rows 13 = columns
	
	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   .,:!?()-" };
	subtitleFont = App->renderer->LoadFont("Pinball/font_CatPaw32.png", lookupTable2, 6, 13); // 6 = rows 13 = columns

	srand(time(NULL));
	startTime = SDL_GetTicks();
	return ret;
}

bool ModuleLeaderboard::CleanUp()
{
	prevScore[0] = prevScore[1];

	App->renderer->UnLoadFont(titleFont);
	App->renderer->UnLoadFont(subtitleFont);
	return true;
}

update_status ModuleLeaderboard::Update()
{
	dTime = SDL_GetTicks() - startTime;
	randNum = rand() % 3000 + 10000;
	
	App->renderer->DrawQuad(bgColor, 162, 209, 255);

	// Animation
	//LOG("%d", randNum);
	if (dTime < 4000 || animLurkingCat.HasFinished() == true)
	{
		animLurkingCat.Update();
		App->renderer->Blit(texLurkingCat, 368, 300, &(animLurkingCat.GetCurrentFrame()), 1.f, 1.f, -90, INT_MAX, INT_MAX, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);

	}
	if (dTime > randNum)
	{
		startTime = SDL_GetTicks();
	}

	// Change screens
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro, 90);
	}
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		//startTime = SDL_GetTicks();
		LOG("startTime: %d\ndTime: %d", startTime, dTime);
	}
	
	ranks();

	// render text
	App->renderer->BlitText(220, 30, titleFont, "HIGH", 0.7f);
	App->renderer->BlitText(170, 80, titleFont, "SCORES", 0.7f);
	for (int i = 0; i < 10; i++)
	{
		string s_num = std::to_string(i+1);
		const char* ch_num = s_num.c_str();
		(i < 9) ? App->renderer->BlitText(85, 164 + 50 * i, titleFont, ch_num, 0.5f)
			: App->renderer->BlitText(53, 164 + 50 * i, titleFont, ch_num, 0.5f);
		App->renderer->BlitText(117, 164 + 50 * i, titleFont, ".", 0.5f);


		string s_score = std::to_string(leaderboard[i]);
		const char* ch_score = s_score.c_str();
		if (leaderboard[i] == currentScore)
		{
			SDL_Rect rect = { 147, 160 + 50 * i, 32 * strlen(ch_score), 40 };
			App->renderer->DrawQuad(rect, 200, 0, 255, 75);
			App->renderer->BlitText(32 * strlen(ch_score) + 170, 167 + 50 * i, subtitleFont, "Current", 0.75f);
		}

		App->renderer->BlitText(150, 164 + 50 * i, subtitleFont, ch_score);	
	}

	App->renderer->BlitText(150, 680, titleFont, "PREVIOUS SCORE", 0.3f);
	string s_Pnum = std::to_string(prevScore[0]);
	const char* ch_Pnum = s_Pnum.c_str();
	App->renderer->BlitText(200, 720, subtitleFont, ch_Pnum);

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleLeaderboard::ranks()
{
	bubbleSort(leaderboard, 10);
	prevScore[1] = currentScore;
}

void ModuleLeaderboard::bubbleSort(int array[], int size)
{
	// loop to access each array element
	for (int step = 0; step < size - 1; ++step) {

		// loop to compare array elements
		for (int i = 0; i < size - step - 1; ++i) {

			// compare two adjacent elements
			// change > to < to sort in descending order
			if (array[i] < array[i + 1]) {

				// swapping occurs if elements
				// are not in the intended order
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}