#include "ModulePlayer.h"
#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
#include "Log.h"
#include "Scene.h"
#include <stdio.h>
#include <time.h>




ModulePlayer::ModulePlayer()
{
	idleAnim.PushBack({ 0, 1, 31, 35 });
	idleAnim.PushBack({ 138, 1, 31, 37 });
	idleAnim.loop = true;
	idleAnim.speed = 0.008f;


	leftAnim.PushBack({ 1, 40, 31, 34 });
	leftAnim.PushBack({ 32, 40, 31, 34 });
	leftAnim.PushBack({ 64, 40, 31, 34 });
	leftAnim.PushBack({ 96, 40, 31, 34 });
	leftAnim.PushBack({ 128, 40, 31, 34 });
	leftAnim.PushBack({ 160, 40, 31, 34 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;



	rightAnim.PushBack({ 1, 80, 31, 34 });
	rightAnim.PushBack({ 32, 80, 31, 34 });
	rightAnim.PushBack({ 64, 80, 31, 34 });
	rightAnim.PushBack({ 96, 80, 31, 34 });
	rightAnim.PushBack({ 128, 80, 31, 34 });
	rightAnim.PushBack({ 160, 80, 31, 34 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake()
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = app->tex->Load("Assets/playerSprites.png");
	currentAnimation = &idleAnim;

	laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 830;
	position.y = 180;

	destroyed = false;


	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;
}

bool ModulePlayer::Update(float dt)
{
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
	{
		position.x -= speed;
		app->render->camera.x -= 3;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
	{
		position.x += speed;
		app->render->camera.x += 3;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (
		app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE)
	{
		currentAnimation = &idleAnim;
	}

	currentAnimation->Update();

	return true;
}

bool ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		
	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &rect);

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//app->fonts->BlitText(58, 248, scoreFont, scoreText);

	//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

	return true;
}

bool ModulePlayer::CleanUp() // Implementar???
{
	return true;
}
