#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	/*app->render->camera.w = 200;
	app->render->camera.h = 200;
	app->render->camera.x = -600;
	app->render->camera.y = -1200;*/

	app->audio->PlayMusic("Assets/audio/music/GamePlaySEGASonic.ogg");
	background = app->tex->Load("Assets/maps/background.png");

	app->map->Enable();
	// L03: DONE: Load map
	app->map->Load("SonicMap.tmx");
	
	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle("Platform Game - LEVEL 1");

	app->render->DrawTexture(background, -150, -400, NULL, 0.75f);
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(background);
	app->map->Disable();

	return true;
}
