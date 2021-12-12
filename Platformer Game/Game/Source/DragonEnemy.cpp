#include "DragonEnemy.h"

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
#include "ModulePlayer.h"
#include "Map.h"
#include "SceneIntro.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "Path.h"
#include "ModuleEnemies.h"
#include "ModuleEnemy.h"


DragonEnemy::DragonEnemy(int x, int y) : ModuleEnemy(x, y)
{
	ModuleEnemy::health = 5;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	idleAnim.PushBack({ 0, 159, 32, 31 });
	idleAnim.PushBack({ 886, 159, 32, 31 });
	idleAnim.loop = true;
	idleAnim.speed = 0.008f;

	//leftAnim
	leftAnim.PushBack({ 885, 192, 33, 32 });
	leftAnim.PushBack({ 851, 193, 34, 31 });
	leftAnim.PushBack({ 819, 192, 32, 32 });
	leftAnim.PushBack({ 786, 192, 33, 32 });
	leftAnim.PushBack({ 753, 193, 33, 31 });
	leftAnim.PushBack({ 721, 192, 32, 32 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//leftShoot
	//leftShotAnim.PushBack({ 1, 119, 31, 37 });
	//leftShotAnim.PushBack({ 31, 117, 30, 39 });
	//leftShotAnim.PushBack({ 61, 121, 31, 35 });
	//leftShotAnim.PushBack({ 92, 121, 29, 35 });
	//leftShotAnim.loop = true;
	//leftShotAnim.speed = 0.8f;

	//rightAnim
	rightAnim.PushBack({ 0, 192, 33, 32 });
	rightAnim.PushBack({ 34, 193, 34, 31 });
	rightAnim.PushBack({ 67, 192, 32, 32 });
	rightAnim.PushBack({ 99, 192, 33, 32 });
	rightAnim.PushBack({ 132, 193, 33, 31 });
	rightAnim.PushBack({ 166, 192, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	//rightShoot
	/*rightShotAnim.PushBack({ 1, 119, 31, 37 });
	rightShotAnim.PushBack({ 31, 117, 30, 39 });
	rightShotAnim.PushBack({ 61, 121, 31, 35 });
	rightShotAnim.PushBack({ 92, 121, 29, 35 });
	rightShotAnim.loop = true;
	rightShotAnim.speed = 0.8f;*/


	//Have the Soldiers describe a path in the screen taking into account the collisions
	

	collider = app->collisions->AddCollider({ position.x, position.y, 20, 20 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS

	dragonCounter.add(app->physics->CreateDragon(position.x, position.y, 20, 20));
	//Walking_Enemy_List.end->data->listener = this;

	;

}

//void DragonEnemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
//{
//	if (bodyA->typeCollision == typeOfCollision::PLAYER && bodyB->typeCollision == typeOfCollision::WINFLAG)
//	{
//		
//	}
//	if (bodyA->typeCollision == typeOfCollision::PLAYER && bodyB->typeCollision == typeOfCollision::FALL)
//	{
//		app->scene->Disable();
//		//app->player->Disable();
//		app->intro->Enable();
//	}
//}

void DragonEnemy::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	//PATHFINDING
	dragonCounter.end->data->GetPosition(position.x, position.y);

	if (position.DistanceTo(app->player->position) < 1000)
	{
		if (position.x < app->player->position.x)
		{
			currentAnim = &rightAnim;
			dragonCounter.end->data->body->SetLinearVelocity({ 1.0f,0.0f });

		}
		if (position.x > app->player->position.x)
		{
			currentAnim = &leftAnim;
			dragonCounter.end->data->body->SetLinearVelocity({ -1.0f,0.0f });

		}
	}

	if ((health == 0) || (app->enemies->active == false))
	{
		dragonCounter.end->data->body->DestroyFixture(dragonCounter.end->data->body->GetFixtureList());
		SetToDelete();
	}
	if (app->enemies->DragonSpawning == true)
	{
		dragonCounter.end->data->body->DestroyFixture(dragonCounter.end->data->body->GetFixtureList());
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	ModuleEnemy::Update(dt);
}
