#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "ModuleFadeToBlack.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "Defs.h"
#include "Log.h"

SceneIntro::SceneIntro() : Module()
{
	name.Create("sceneIntro");
}

// Destructor
SceneIntro::~SceneIntro()
{}

// Called before render is available
bool SceneIntro::Awake(pugi::xml_node& config)
{
	LOG("Loading Intro");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool SceneIntro::Start()
{
	// L03: DONE: Load map
	//app->audio->PlayMusic("Assets/audio/music/introMusic.ogg");
	backgroundIntro = app->tex->Load("Assets/maps/introImage.png");
	startButton = app->tex->Load("Assets/textures/PressEnterToStartRed.png");
	loading = app->tex->Load("Assets/maps/loadingScreen.png");

	app->render->camera.x = app->map->MapToWorld(0, -130).x;
	app->render->camera.y = app->map->MapToWorld(0, -130).y;


	sCounter = 0;
	delay = 0;
	nextImage = false;

	return true;
}

// Called each loop iteration
bool SceneIntro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneIntro::Update(float dt)
{
	app->scene->Disable();
	app->player->Disable();
	
	sCounter++;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		nextImage = true;
		app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
	}

	if (nextImage == true) delay++;

	if (delay > 90 && delay <= 91)
	{
		app->map->Enable();
		app->scene->Enable();
		app->player->Enable();
		/*app->enemies->Enable();*/
		//app->physics->Enable();

		app->intro->Disable();
	}

	return true;
}

// Called each loop iteration
bool SceneIntro::PostUpdate()
{
	bool ret = true;
	
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}
	app->render->DrawTexture(backgroundIntro, 0, 2080, NULL, 1.0f);
	
	if ((sCounter / 40) % 2 == 0)
	{
		app->render->DrawTexture(startButton, 100, 2180, NULL, 1.0f);
	}

	if(nextImage == true) app->render->DrawTexture(loading, 0, 2080, NULL);

	return ret;
}

// Called before quitting
bool SceneIntro::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(backgroundIntro);
	app->tex->UnLoad(startButton);
	app->tex->UnLoad(loading);
	return true;
}



