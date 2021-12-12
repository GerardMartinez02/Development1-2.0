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


DragonEnemy::DragonEnemy(int x, int y) : ModuleEnemy(x, y)
{
	ModuleEnemy::health = 5;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

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

	/*if (position.DistanceTo(app->player->position) < 1000)
	{
		if (position.x < app->player->position.x)
		{
			currentAnim = &Walking_Enemy_Right;
			Walking_Enemy_List.end->data->body->SetLinearVelocity({ 1.0f,0.0f });

		}
		if (position.x > app->player->position.x)
		{
			currentAnim = &Walking_Enemy_Left;
			Walking_Enemy_List.end->data->body->SetLinearVelocity({ -1.0f,0.0f });

		}
	}

	if ((health == 0) || (app->enemies->active == false))
	{
		Walking_Enemy_List.end->data->body->DestroyFixture(Walking_Enemy_List.end->data->body->GetFixtureList());
		SetToDelete();
	}
	if (app->enemies->GoombaLoading == true)
	{
		Walking_Enemy_List.end->data->body->DestroyFixture(Walking_Enemy_List.end->data->body->GetFixtureList());
	}*/

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	ModuleEnemy::Update(dt);
}
