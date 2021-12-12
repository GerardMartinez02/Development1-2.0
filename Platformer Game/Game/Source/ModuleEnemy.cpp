#include "ModuleEnemy.h"
#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
#include "Log.h"
#include "Scene.h"
#include "ModulePhysics.h"
#include "Map.h"
#include "SceneIntro.h"
#include "Collider.h"
#include "ModuleEnemies.h"
#include "Particles.h"
#include "ModuleParticles.h"

ModuleEnemy::ModuleEnemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

ModuleEnemy::~ModuleEnemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void ModuleEnemy::Update(float dt)
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	//if ((App->player->position.x - App->particles->enemyShoot.spawnPos.x) < 0) direction.x = -1.0f;
	//else if ((App->player->position.x - App->particles->enemyShoot.spawnPos.x) > 0)direction.x = 1.0f;
	//else direction.x = 0.0f;
}

void ModuleEnemy::Draw()
{
	if (currentAnim != nullptr)
		app->render->DrawTexture(Enemytexture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void ModuleEnemy::OnCollision(Collider* collider)
{
	app->particles->AddParticle(app->particles->explosion, position.x, position.y);
	app->audio->PlayFx(destroyedFx);

	SetToDelete();
}

void ModuleEnemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}