#pragma once

#include "p2List.h"
#include "Globals.h"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModulePhysics;

class ModuleFadeToBlack;

class ModuleLeaderboard;
class ModuleSceneIntro;
class ModuleScene;
class ModulePlayer;


class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePhysics* physics;

	ModuleFadeToBlack* fade;
	
	ModuleLeaderboard* scene_lead;
	ModuleSceneIntro* scene_intro;
	ModuleScene* scene;
	ModulePlayer* player;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};