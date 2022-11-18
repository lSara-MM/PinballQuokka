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

ModuleLeaderboard::ModuleLeaderboard(Application* app, bool start_enabled) : Module(app, start_enabled)
{

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
	

	// Load Font
	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789   .,:!?()-" };
	titleFont = App->renderer->LoadFont("Pinball/font_CatPaw.png", lookupTable1, 4, 13); // 4 = rows 13 = columns
	
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
	//App->renderer->Blit(map,0,0);

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

	
	if (dTime < 1500)
	{
		App->renderer->BlitText(85, 600, subtitleFont, "Press ENTER");
		App->renderer->BlitText(120, 650, subtitleFont, "to start");
	}
	if (dTime > 2500) { startTime = SDL_GetTicks(); }
	
	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleLeaderboard::ranks()
{
	SDL_Rect bgColor;
	bgColor = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE,  SCREEN_HEIGHT * SCREEN_SIZE };

	SDL_RenderFillRect(App->renderer->renderer, &bgColor);
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