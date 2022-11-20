#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleLeaderboard.h"

#include <iostream>
using namespace std;
#include <sstream>

#include "Animation.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	animPlayCat.PushBack({ 0, 0, 480, 480 });
	animPlayCat.PushBack({ 0, 0, 480, 480 });
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			animPlayCat.PushBack({ 480 * j, 480 * i, 480, 480 });
		}
	}

	animPlayCat.PushBack({ 480 * 4, 0, 480, 480 });
	animPlayCat.PushBack({ 480 * 4, 480, 480, 480 });
	animPlayCat.PushBack({ 480 * 4, 480 * 2, 480, 480 });
	animPlayCat.PushBack({ 480 * 4, 480 * 3, 480, 480 });

	animPlayCat.loop = true;
	animPlayCat.speed = 0.2f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//Music
	App->audio->PlayMusic("pinball/Music.ogg");

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	bgTexture = App->textures->Load("pinball/introBg.png");
	texPlayCat = App->textures->Load("pinball/ss_playCat.png");

	// Load Font
	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789   .,:!?()-" };
	titleFont = App->renderer->LoadFont("Pinball/font_QuietMeows.png", lookupTable1, 4, 13); // 4 = rows 13 = columns
	
	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   .,:!?()-" };
	subtitleFont = App->renderer->LoadFont("Pinball/font_CatPaw32.png", lookupTable2, 6, 13); // 6 = rows 13 = columns

	startTime = SDL_GetTicks();
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	// Clear fonts
	App->renderer->UnLoadFont(titleFont);
	App->renderer->UnLoadFont(subtitleFont);

	//Clear textures
	App->textures->Unload(bgTexture);
	App->textures->Unload(texPlayCat);
	return true;
}

update_status ModuleSceneIntro::Update()
{
	dTime = SDL_GetTicks() - startTime;

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
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_lead, 0);
	}

	// Render 
	App->renderer->Blit(bgTexture, 0, 0);

	App->renderer->BlitText(90, 30, titleFont, "CATBALL");
	App->renderer->BlitText(145, 110, subtitleFont, "by Quokka Stu(d)i(os)", 0.5f);

		// Animation
	animPlayCat.Update();
	App->renderer->Blit(texPlayCat, 20, 130, &(animPlayCat.GetCurrentFrame()));

		// Blinking text
	if (dTime < 1500)
	{
		App->renderer->BlitText(110, 650, subtitleFont, "Press ENTER");
		App->renderer->BlitText(150, 690, subtitleFont, "to start");
	}
	if (dTime > 2500) { startTime = SDL_GetTicks(); }
	
	// Keep playing
	return UPDATE_CONTINUE;
}
