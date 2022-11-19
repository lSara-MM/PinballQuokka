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

#include "Animation.h"

ModuleLeaderboard::ModuleLeaderboard(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			animLurkingCat.PushBack({ 640 * j, 640 * i, 640, 640 });
			if (i == 3 && j == 3) { break; }
		}
	}
	animLurkingCat.loop = true;
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
	bgTexture = App->textures->Load("pinball/map.png");
	texLurkingCat = App->textures->Load("pinball/ss_LurkingCat.png");

	// Load Font
	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789   .,:!?()-" };
	titleFont = App->renderer->LoadFont("Pinball/font_QuietMeows.png", lookupTable1, 4, 13); // 4 = rows 13 = columns
	
	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   .,:!?()-" };
	subtitleFont = App->renderer->LoadFont("Pinball/font_CatPaw32.png", lookupTable2, 6, 13); // 6 = rows 13 = columns

	//startTime = SDL_GetTicks();
	return ret;
}

bool ModuleLeaderboard::CleanUp()
{
	return true;
}

update_status ModuleLeaderboard::Update()
{
	dTime = SDL_GetTicks() - startTime;
	//Dibujar el mapa
	App->renderer->Blit(bgTexture, 0, 0);

	App->renderer->Blit(texLurkingCat, -100, 0, NULL, 1.f, 1.f, 90, 0, 0, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		startTime = SDL_GetTicks();
		LOG("startTime: %d\ndTime: %d", startTime, dTime);
	}
	
	App->renderer->BlitText(200, 30, titleFont, "HIGH", 0.7f);
	App->renderer->BlitText(150, 80, titleFont, "SCORES", 0.7f);
	for (int i = 0; i < 10; i++)
	{
		string s_num = std::to_string(i+1);
		const char* ch_num = s_num.c_str();
		(i < 9) ? App->renderer->BlitText(85, 164 + 50 * i, titleFont, ch_num, 0.5f)
			: App->renderer->BlitText(53, 164 + 50 * i, titleFont, ch_num, 0.5f);
		App->renderer->BlitText(117, 164 + 50 * i, titleFont, ".", 0.5f);
	}


	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleLeaderboard::ranks()
{
	bubbleSort(leaderboard, 10);
}

void ModuleLeaderboard::bubbleSort(int array[], int size)
{
	// loop to access each array element
	for (int step = 0; step < size - 1; ++step) {

		// loop to compare array elements
		for (int i = 0; i < size - step - 1; ++i) {

			// compare two adjacent elements
			// change > to < to sort in descending order
			if (array[i] > array[i + 1]) {

				// swapping occurs if elements
				// are not in the intended order
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}