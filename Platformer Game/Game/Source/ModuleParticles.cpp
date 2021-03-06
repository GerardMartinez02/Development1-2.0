#include "ModuleParticles.h"

#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Window.h"
#include "Log.h"
#include "Scene.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "Map.h"
#include "SceneIntro.h"
#include "Textures.h"

#include "SDL/include/SDL_timer.h"
#include <stdio.h>

ModuleParticles::ModuleParticles() : Module()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = app->tex->Load("Assets/textures/EnemiesSprites.png");

	// Explosion particle
	//explosion.anim.PushBack({ 85, 91, 23, 22 });
	//explosion.anim.PushBack({ 116, 88, 35, 31 });
	//explosion.anim.PushBack({ 151, 88, 38, 30 });
	//explosion.anim.PushBack({ 188, 86, 35, 31 });
	//explosion.anim.PushBack({ 225, 84, 36, 33 });
	//explosion.anim.PushBack({ 262, 84, 36, 32 });
	//explosion.anim.PushBack({ 298, 83, 38, 34 });
	//explosion.anim.PushBack({ 335, 80, 37, 34 });
	//explosion.anim.loop = false;
	//explosion.anim.speed = 0.3f;

	//players death
	//death.anim.PushBack({ 60, 311, 36, 30 });
	//death.anim.PushBack({ 102, 310, 44, 33 });
	//death.anim.PushBack({ 152, 313, 47, 35 });
	//death.anim.PushBack({ 201, 312, 45, 39 });
	//death.anim.PushBack({ 247, 307, 52, 43 });
	//death.anim.PushBack({ 296, 308, 50, 45 });
	//death.anim.PushBack({ 352, 306, 44, 45 });
	//death.anim.PushBack({ 404, 305, 48, 48 });
	//death.anim.PushBack({ 58, 352, 42, 48 });
	//death.anim.PushBack({ 79, 352, 39, 48 });
	//death.anim.PushBack({ 110, 352, 43, 54 });
	//death.anim.PushBack({ 156, 352, 49, 52 });
	//death.anim.PushBack({ 205, 351, 49, 55 });
	//death.anim.PushBack({ 254, 352, 50, 53 });
	//death.anim.PushBack({ 304, 352, 51, 49 });
	//death.anim.PushBack({ 355, 352, 50, 53 });
	//death.anim.PushBack({ 409, 364, 42, 41 });
	//death.anim.loop = false;
	//death.speed.y -= 2;
	//death.anim.speed = 0.1f;

	
	//shoot anim
	//laser.anim.PushBack({ 304, 420, 23, 25 });
	//laser.speed.y -= 5;
	//laser.lifetime = 180;
	//laser.anim.speed = 0.2f;

	//enemy shoot
	/*enemyShoot.anim.PushBack({ 251, 452, 15, 15 });
	enemyShoot.speed.y = 2.0f;
	enemyShoot.lifetime = 300;
	enemyShoot.anim.speed = 0.2f;

	enemyShootL.anim.PushBack({ 251, 452, 15, 15 });
	enemyShootL.speed.y += 2;
	enemyShootL.speed.x -= 1;
	enemyShootL.lifetime = 110;
	enemyShootL.anim.speed = 0.2f;

	enemyShootR.anim.PushBack({ 251, 452, 15, 15 });
	enemyShootR.speed.y = 2.0f;
	enemyShootR.speed.x += 1;
	enemyShootR.lifetime = 100;
	enemyShootR.anim.speed = 0.2f;*/

	return true;
}

bool ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* bodyA, Collider* bodyB)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == bodyA)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

bool ModuleParticles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update(dt) == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return true;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay, bool track)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = app->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;

			newParticle->spawnPos.x = x;
			newParticle->spawnPos.y = y;

			if (track == true)
			{
				if ((app->player->position.x - x) < 0) newParticle->speed.x = -1.0f;
				else if ((app->player->position.x - x) > 0)newParticle->speed.x = 1.0f;
				else newParticle->speed.x = 0.0f;

				if (((app->player->position.y ^ 2) - (y ^ 2)) < 0) newParticle->speed.y = -2.0f;
				else if (((app->player->position.y ^ 2) - (y ^ 2)) > 0) newParticle->speed.y = 2.0f;
				else newParticle->speed.y = 0.0f;
			}
			break;
		}
	}

	return newParticle;
}