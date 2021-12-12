#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"

#define MAX_ENEMIES 200

enum class Enemy_Type
{
	NO_TYPE,
	DRAGONENEMY,
	BIRDENEMY
};

struct EnemySpawnpoint
{
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x, y;
};

class ModuleEnemy;
struct SDL_Texture;

class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies();

	// Destructor
	~ModuleEnemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired

	void OnCollision(Collider* bodyA, Collider* bodyB) override;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	ModuleEnemy* enemies[MAX_ENEMIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* EnemiesTextures = nullptr;

	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__#pragma once
