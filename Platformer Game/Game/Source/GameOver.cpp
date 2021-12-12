//#include "GameOver.h"
//#include "App.h"
//#include "Input.h"
//#include "Textures.h"
//#include "Audio.h"
//#include "Render.h"
//#include "Window.h"
//#include "Scene.h"
//#include "Map.h"
//#include "ModulePhysics.h"
//#include "ModulePlayer.h"
//#include "ModuleFadeToBlack.h"
//#include "Defs.h"
//#include "Log.h"
//
//#include "Defs.h"
//#include "Log.h"
//
//GameOver::GameOver()
//{
//	name.Create("gameOver");
//}
//
//// Destructor
//GameOver::~GameOver()
//{}
//
//// Called before render is available
//bool GameOver::Awake(pugi::xml_node& config)
//{
//	LOG("Loading Death");
//	bool ret = true;
//	
//	return ret;
//}
//
//// Called before the first frame
//bool GameOver::Start()
//{
//	gameOverImg = app->tex->Load("Assets/maps/gameOver.png");
//
//	app->map->Disable();
//	
//	app->player->Disable();
//	
//	app->render->camera.x = app->render->camera.y = 0;
//	return true;
//}
//
//// Called each loop iteration
//bool GameOver::PreUpdate()
//{
//	return true;
//}
//
//// Called each loop iteration
//bool GameOver::Update(float dt)
//{
//	bool ret = true;
//	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
//	{
//		if (app->player->death)
//		{
//			app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
//		}
//			
//		
//	}
//
//
//	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
//		ret = false;
//
//	app->render->camera.x = app->render->camera.y = 0;
//	if (app->player->death)
//	{
//		app->render->DrawTexture(gameOverImg, 0, 0, NULL, 1.0f);
//				
//	}
//	/*if (app->player->win)
//	{
//		app->render->DrawTexture(WinImage, 0, 0, NULL);
//	}*/
//
//	return ret;
//}
//
//// Called each loop iteration
//bool GameOver::PostUpdate()
//{
//	bool ret = true;
//	return ret;
//}
//
//// Called before quitting
//bool GameOver::CleanUp()
//{
//	LOG("Freeing scene");
//	app->tex->UnLoad(gameOverImg);
//
//	return true;
//}